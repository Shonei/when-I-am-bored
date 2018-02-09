import React, { Component } from 'react';
import { Row, Col, Button } from 'react-materialize';
import Item from './../Item';

class Scrabble extends Component {
  constructor(props) {
    super(props);

    this.state = {
      body: <div></div>
    };

    this.handleClick = this.handleClick.bind(this);
  }

  // loads all the players from the Database and displayes hteir pofile picture and name
  componentDidMount() {
    this.props.database.ref('scrabble/members').once('value').then(snapshot => {
      const arr = [];
      for (let key in snapshot.val()) {
        const item = <Col key={key} s={12} m={6} l={4}><Item
          title={key} img={snapshot.val()[key].img}
          onclick={(e) => this.handleClick(key)} />
        </Col>;
        arr.push(item);
      }

      this.setState({ body: <Row>{arr}</Row> });
    });
  }

  handleClick(user) {
    this.props.database.ref('scrabble/members/' + user).once('value').then(snapshot => {
      let temp = snapshot.val();
      temp.uname = user;
      window.localStorage.setItem('user', window.JSON.stringify(temp));
      window.location.href = 'scrabble/user';
    });
  }

  render() {
    return (
      <div>
        <Row></Row>
        <div className="container">
          {this.state.body}
          <Row className="center-align">
            <a href="scrabble/leaderboard">
              <Button waves="light">Leaderborads</Button>
            </a>
          </Row>
        </div>
      </div>
    );
  }
}

export default Scrabble;