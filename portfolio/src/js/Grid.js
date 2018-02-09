import React, { Component } from 'react';
import { Row, Col } from 'react-materialize';
import scrabble from '../img/scrabble.jpg';
import ds from '../img/ds.png';
import sis from '../img/sis.png';
import website from '../img/website.png';
import Item from './Item';

class Grid extends Component {
  render() {
    return (
      <div className="container">
        <Row>
          <Col s={12} m={6} l={3}>
            <Item title="Scrabble" URL="scrabble" img={scrabble} />
          </Col>
          <Col s={12} m={6} l={3}>
            <Item title="Distributed systems" URL="ds" img={ds} />
          </Col>
          <Col s={12} m={6} l={3}>
            <Item title="Final year project" URL="https://sis-shonei.herokuapp.com/" img={sis} />
          </Col>
          <Col s={12} m={6} l={3}>
            <Item title="My first website" URL="https://website-6de1e.firebaseapp.com" img={website} />
          </Col>
        </Row>
      </div>
    );
  }
}

export default Grid;