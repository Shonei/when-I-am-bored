import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import { Navbar, NavItem } from 'react-materialize';
import Grid from './Grid';
import Scrabble from './Scrabble';
import User from './User';
import Lead from './Leaderboard';
import MainDs from './main-ds';

class Nav extends Component {
  constructor(props) {
    super(props);

    this.mainBody = {
      '/scrabble': <Scrabble></Scrabble>,
      '/': <Grid></Grid>
    };
  }

  componentDidMount() {
    if (window.location.pathname === '/scrabble') {
      ReactDOM.render(<Scrabble
        database={this.props.firebase.database()}>
      </Scrabble>, document.getElementById('content'));
    } else if (window.location.pathname === '/') {
      ReactDOM.render(<Grid></Grid>, document.getElementById('content'));
    } else if (window.location.pathname === '/scrabble/user') {
      ReactDOM.render(<User
        database={this.props.firebase.database()}>
      </User>, document.getElementById('content'));
    } else if (window.location.pathname === '/scrabble/leaderboard') {
      ReactDOM.render(<Lead
        database={this.props.firebase.database()}>
      </Lead>, document.getElementById('content'));
    } else if (window.location.pathname === '/ds') {
      ReactDOM.render(<MainDs
        database={this.props.firebase.database()}>
      </MainDs>, document.getElementById('content'));
    }
  }

  render() {
    return (
      <div>
        <Navbar className="indigo lighten-3">
          <NavItem href="/" className="indigo lighten-3">Home</NavItem>
          <NavItem target="_blank" href="/cv.html" className="indigo lighten-3">CV</NavItem>
          <NavItem href="https://github.com/Shonei" className="indigo lighten-3">Github</NavItem>
        </Navbar>
      </div>
    );
  }
}

export default Nav;

