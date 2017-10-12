import React, { Component } from 'react';
import {Navbar, NavItem, Icon, Button, Dropdown} from 'react-materialize';
import './Navbar.css';

class Nav extends Component {
  render() {
    return (
      <div>
        <Navbar className="indigo lighten-3" brand="logo" left>
          <NavItem href="/" className="indigo lighten-5">About me</NavItem>
          <NavItem href="/cv.html" className="indigo lighten-5">About me</NavItem>
          <Dropdown trigger={<Button>Projects</Button>}>
            <NavItem>one</NavItem>
            <NavItem>two</NavItem>
            <NavItem divider />
            <NavItem>three</NavItem>
          </Dropdown>
        </Navbar>
      </div>
    );
  }
}

export default Nav;

