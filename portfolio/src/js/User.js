import React, { Component } from 'react';
import {Breadcrumb, MenuItem, Row, Col} from 'react-materialize';

class User extends Component {
  constructor(props) {
    super(props);

    this.state = {
      user : null
    };

    this.getBody = this.getBody.bind(this);
    this.componentDidMount = this.componentDidMount.bind(this);
  }
  
  componentDidMount() {
    const user = window.localStorage.getItem('user');
    this.setState({user: window.JSON.parse(user)});  
  }

  getBody() {
    const user = this.state.user;
    if(!user) {
      return <p>No user</p>;
    } else {
      return <img className="center-align" src={user.img} alt="source"/>
    }
  }

  render() {
    return (
      <div>
        <Breadcrumb>
          <MenuItem href="/">Home page</MenuItem>
          <MenuItem href="/scrabble">Scrabble</MenuItem>
          <MenuItem href="/scrabble/user">Scrabble</MenuItem>
        </Breadcrumb>
        <Row></Row>
        <div className="container">
          {this.getBody()}
        </div>
      </div>
    );
  }
}

export default User;