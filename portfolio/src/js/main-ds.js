import React, { Component } from 'react';
import Search from './Search';
import Saved from './Saved';

const a = {
  // lineHeight: '1em',
  // display: 'inline - block',
  // textDecoration: 'none',
  // padding: '2px',
  margin: '2px'
};

class MainDs extends Component {
  constructor(props) {
    super(props);

    this.state = {
      body: <Search></Search>
    };
  }

  render() {
    return (
      <div>
        <br />
        <div>
          <a style={a} onClick={() => this.setState({ body: <Search></Search> })} className="waves-effect waves-light btn"><i className="material-icons left">folder</i>Search</a>
          <a style={a} onClick={() => this.setState({ body: <Saved></Saved> })} className="waves-effect waves-light btn"><i className="material-icons left">folder</i>Saved</a>
        </div>
        {this.state.body}
      </div>
    );
  }
}

export default MainDs;