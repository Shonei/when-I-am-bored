import React, { Component } from 'react';
import {Breadcrumb, MenuItem, Row, Col} from 'react-materialize';
import Item from './Item';

class Scrabble extends Component {
  constructor(props) {
    super(props);

    this.state = {
      body: <div></div>
    };

    this.handleClick = this.handleClick.bind(this);
    
    this.props.database.ref('scrabble/members').once('value').then(snapshot => {
      const arr = [];
      for(let key in snapshot.val()) {
        const item = <Col key={key} s={4}><Item 
                          title={key} img={snapshot.val()[key].img} 
                          onclick={(e)=>this.handleClick(key)}/>
                      </Col>;
        arr.push(item);
      }

      this.setState({body:<Row>{arr}</Row>});
    });
  }

  handleClick(user) {
    this.props.database.ref('scrabble/members/'+user).once('value').then(snapshot => {
      window.localStorage.setItem('user', window.JSON.stringify(snapshot.val()));
      window.location.href = 'scrabble/user';
    });
  }

  render() {
    return (
      <div>
        <Breadcrumb>
          <MenuItem href="/">Home page</MenuItem>
          <MenuItem href="/scrabble">Scrabble</MenuItem>
        </Breadcrumb>
        <Row></Row>
        <div className="container">
          {this.state.body}
        </div>
      </div>
    );
  }
}

export default Scrabble;