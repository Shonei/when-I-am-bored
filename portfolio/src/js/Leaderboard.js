import React, { Component } from 'react';
import {Row, Col} from 'react-materialize';
import '../css/leaderboard.css';


class Lead extends Component {
  render() {
    return (
      <div className="container">
        <h3 className="center-align">Leaderboard</h3>
        <Row>
          <Col className="center-align" s={12}>
          <img className="responsive-img materialboxed" src="https://firebasestorage.googleapis.com/v0/b/shonei-portfolio.appspot.com/o/p1.jpeg?alt=media&token=d526fc2b-ad41-40be-a93f-4dc77f8ff179" alt="ghdfg"/>
          <p><b>1st. </b>Shonei</p>
          </Col>
        </Row>
      </div>
    );
  }
}

export default Lead;