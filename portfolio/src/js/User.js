import React, { Component } from 'react';
import {Breadcrumb, MenuItem, Row, Col, Input, Icon, Collection, CollectionItem, Button} from 'react-materialize';

class User extends Component {
  constructor(props) {
    super(props);

    this.state = {
      user : null,
      editing: false
    };

    this.getBody = this.getBody.bind(this);
    this.componentDidMount = this.componentDidMount.bind(this);
    // this.editProfile = this.editProfile.bind(this);
    this.getProfile = this.getProfile.bind(this);
    this.update = this.update.bind(this);
  }
  
  componentDidMount() {
    const user = window.localStorage.getItem('user');
    this.setState({user: window.JSON.parse(user)});  
  }

  update() {
    let temp = this.state.user;
    temp.f_name = document.getElementById('f_name').value;
    temp.l_name = document.getElementById('l_name').value;
    temp.email = document.getElementById('email').value;
    temp.phone = document.getElementById('phone').value;
    
    this.props.database.ref('scrabble/members/' + temp.uname).update(temp);
    
    this.setState({user : temp});
    this.setState({editing : false});

    window.localStorage.setItem('user', window.JSON.stringify(this.state.user));
  }

  getProfile() {
    if(this.state.editing) {
      return (
        <Col s={12} m={6}>
          <Input id="f_name" s={12} label="First name" defaultValue={this.state.user.f_name} ></Input>
          <Input id="l_name" s={12} label="Last name" defaultValue={this.state.user.l_name} ></Input>
          <Input id="email" s={12} label="Email" defaultValue={this.state.user.email} ></Input>
          <Input id="phone" s={12} label="Phone number" defaultValue={this.state.user.phone} ></Input>
          <Collection>
            <CollectionItem><b>Username: </b>{this.state.user.uname}</CollectionItem>
          </Collection>
          <Button s={6} waves="light" onClick={this.update}><Icon left>update</Icon>Update</Button>
          <Button s={6} waves="light" onClick={()=>this.setState({editing:false})}>Cancel</Button>
        </Col>
      );
    } else {
      return (
        <Col s={12} m={6}>
          <Collection>
            <CollectionItem><b>Name: </b>{this.state.user.f_name + ' ' + this.state.user.l_name}</CollectionItem>
            <CollectionItem><b>Email: </b>{this.state.user.email}</CollectionItem>
            <CollectionItem><b>Phone: </b>{this.state.user.phone}</CollectionItem>
            <CollectionItem><b>Username: </b>{this.state.user.uname}</CollectionItem>
          </Collection>
          <Button waves="light" onClick={()=>this.setState({editing:true})}><Icon left>edit</Icon>Edit</Button>
        </Col>
      );
    }
  }

  getBody() {
    const user = this.state.user;
    if(!user) {
      return <Row><p className="center-align">User not found</p></Row>;
    } else {
      return (
        <div>
          <Row>
            <Col s={12} m={6}>
              <img className="responsive-img materialboxed" src={user.img} alt="source"/>
            </Col>
              <Col s={12} m={6}>
                <Collection>
                  <CollectionItem><b>Wins: </b>{this.state.user.wins}</CollectionItem>
                  <CollectionItem><b>Losses: </b>{this.state.user.losses}</CollectionItem>
                  <CollectionItem><b>Highest Score: </b>{this.state.user.highest_score}</CollectionItem>
                  <CollectionItem><b>Agains: </b>{this.state.user.agains}</CollectionItem>
                  <CollectionItem><b>When: </b>{this.state.user.when}</CollectionItem>
                  <CollectionItem><b>Where: </b>{this.state.user.where}</CollectionItem>
                  <CollectionItem><b>Average score: </b>Not applicable.</CollectionItem>
                </Collection>
            </Col>
          </Row>
          <Row>
            {this.getProfile()}  
          </Row>
        </div>
      );
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