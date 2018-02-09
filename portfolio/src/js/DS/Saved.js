import React, { Component } from 'react';

class Saved extends Component {
  constructor(props) {
    super(props);

    this.state = {
      body: []
    };

    this.generateTweet = this.generateTweet.bind(this);
  }

  componentDidMount() {
    this.props.database.ref('tweets').once('value').then(snapshot => {
      const tweets = snapshot.val();
      for(let key in tweets) {
        this.generateTweet(tweets[key], key);
      }
    });
  }

  generateTweet(tweet, index) {
    const t = <div key={index}>
      <li className="collection-item avatar">
        <span className="title"><b>User:</b> {tweet.uname}</span>
        <p><b>Content: </b>{tweet.original}</p>
        <p><b>Translated: </b>{tweet.translated}</p>
      </li>
    </div>;

    let arr = this.state.body;
    arr.push(t);
    this.setState({ body: arr });
  }

  render() {
    return (
      <div>
        <ul className="collection">
          {this.state.body}
        </ul>
      </div>
    );
  }
}

export default Saved;