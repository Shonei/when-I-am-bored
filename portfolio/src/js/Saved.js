import React, { Component } from 'react';
import fetch from 'node-fetch';

class Saved extends Component {
  constructor(props) {
      super(props);
  }

  componentDidMount() {
    // fetch('http://localhost:8080')
    // .then((el)=>el.json())
    // .then(console.log)
    // .catch(console.log)
  }

  render() {
    return (
      <div>Saved tweets go here</div>
    );
  }
}

export default Saved;