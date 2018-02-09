import React, { Component } from 'react';
import Search from './Search';
import Saved from './Saved';

const a = {
  margin: '2px'
};

class MainDs extends Component {
  constructor(props) {
    super(props);

    this.state = {
      body: <Search database={this.props.database}></Search>
    };
  }

  render() {
    return (
      <div>
        <br />
        <div className="container">
          <a style={a} onClick={() => this.setState({ body: <Search database={this.props.database}></Search> })} className="waves-effect waves-light btn"><i className="material-icons left">folder</i>Search</a>
          <a style={a} onClick={() => this.setState({ body: <Saved database={this.props.database}></Saved> })} className="waves-effect waves-light btn"><i className="material-icons left">folder</i>Saved</a>
        </div>
        {this.state.body}
      </div>
    );
  }
}

export default MainDs;