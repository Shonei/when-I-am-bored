import React, { Component } from 'react';
import {Row, Col, Input, Icon, Collection, CollectionItem, Button} from 'react-materialize';

class User extends Component {
  constructor(props) {
    super(props);

    this.state = {
      user : null,
      editing: false,
      average: null
    };

    this.getBody = this.getBody.bind(this);
    this.componentDidMount = this.componentDidMount.bind(this);
    // this.editProfile = this.editProfile.bind(this);
    this.getProfile = this.getProfile.bind(this);
    this.update = this.update.bind(this);
  }
  
  componentDidMount() {
    // get the user from local storage
    let user = window.localStorage.getItem('user');
    user = window.JSON.parse(user);
    this.setState({user: user});  

    // read the games where a user has played in and calculate the average
    // once the first set of games are read the function will return a promise
    // that contains the curent total score and the number of games
    // after both wins and losses have been calculated we will calculate the average as well.
    const ref = this.props.database.ref('scrabble/games/'); 
    // user has won games
    ref.orderByChild('po_uname').equalTo(user.uname).once('value').then(snapshot => {
      let obj = {
        games: 0,
        score: 0
      };

      const val = snapshot.val();
      const keys = Object.keys(val);

      obj.games += keys.length;
      Object.keys(val).forEach(e => obj.score += parseInt(val[e].po_score, 10));
      return Promise.resolve(obj);
    }).then(obj => {
      // reads the users losses
      return ref.orderByChild('pt_uname').equalTo(user.uname).once('value').then(snapshot => {
        const val = snapshot.val();
        const keys = Object.keys(val);

        obj.games += keys.length;
        Object.keys(val).forEach(e => obj.score += parseInt(val[e].pt_score, 10));
        return Promise.resolve(obj);
      });
    }).then(score => {
      // calculates average
      this.setState({ average: score.score / score.games });
    });
  }

  // handles the click when a profile has to be updated
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

  // Based on the state it will return a different UI allowing for viewing and editing of data
  getProfile() {
    if(this.state.editing) {
      // if editing is enabled we use the Inputs to show the data allowing ofr changes to be made
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
      // shows this before we have read the users data
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
                  <CollectionItem><b>Average score: </b>{this.state.average}</CollectionItem>
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
        <Row></Row>
        <div className="container">
          {this.getBody()}
        </div>
      </div>
    );
  }
}

export default User;