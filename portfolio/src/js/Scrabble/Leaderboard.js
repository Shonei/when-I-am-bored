import React, { Component } from 'react';
import {Row, Col} from 'react-materialize';

const p = {
  fontSize: '20px'
};

const img = {
  maxHight: '60px',
  maxWidth: '60px'
};

class Leaderboard extends Component {
  constructor(props) {
    super(props);

    this.state = {
      users: <div></div>
    };

    this.componentDidMount = this.componentDidMount.bind(this);
  }

  // Loads the members and creates an array of Col that contains each member 
  // in the leader board
  componentDidMount() {
    this.props.database.ref('scrabble/members').orderByChild('wins').once('value').then(snapshot => {
      const arr = [];
      let place = 1;
      const vals = snapshot.val();
      
      for(let key in vals) {
        const temp =  
          <Col key={key} s={12}>
            <p style={p}><img style={img} src={vals[key].img} alt={key}/>
              <b>{place} </b>{key}</p>
          </Col>;
        arr.push(temp);
        place++;
      }

      this.setState({users:arr});
    });
  }

  render() {
    return (
      <div>
        <div className="container">
          <h3 className="center-align">Leaderboard</h3>
          <Row>
            {this.state.users}
          </Row>
        </div>
      </div>
    );
  }
}

export default Leaderboard;