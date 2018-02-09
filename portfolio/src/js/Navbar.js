import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import { Navbar, NavItem } from 'react-materialize';
import Grid from './Grid';
import Scrabble from './Scrabble/Scrabble';
import User from './Scrabble/User';
import Leaderboard from './Scrabble/Leaderboard';
import MainDs from './DS/main-ds';
import { BrowserRouter as Router, Route } from 'react-router-dom';

class Nav extends Component {
  constructor(props) {
    super(props);

    this.mainBody = {
      '/scrabble': <Scrabble></Scrabble>,
      '/': <Grid></Grid>
    };
  }

  render() {
    return (
      <div>
        <Navbar className="indigo lighten-3">
          <NavItem href="/" className="indigo lighten-3">Home</NavItem>
          <NavItem target="_blank" href="/cv.html" className="indigo lighten-3">CV</NavItem>
          <NavItem href="https://github.com/Shonei" className="indigo lighten-3">Github</NavItem>
        </Navbar>
        <Router>
          <div>
            <Route exact path="/" component={Grid} />
            <Route exact path="/scrabble" render={() => <Scrabble database={this.props.firebase.database()} />} />
            <Route exact path="/scrabble/user" render={() => <User database={this.props.firebase.database()} />} />
            <Route exact path="/scrabble/leaderboard" render={() => <Leaderboard database={this.props.firebase.database()} />} />
            <Route exact path="/ds" render={() => <MainDs database={this.props.firebase.database()} />} />
          </div>
        </Router>
      </div>
    );
  }
}

export default Nav;

