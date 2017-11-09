import React, { Component } from 'react';
import Tweet from './Tweet';

const iStyle = {
  cursor: 'pointer'
};

class Search extends Component {
  constructor(props) {
    super(props);   

    this.state = {
      translate : null,
      lang: 'bg',
      tweets: []
    };

    this.start = this.start.bind(this);
    this.translate = this.translate.bind(this);
    this.saveTweet = this.saveTweet.bind(this);
  }

  componentDidMount() {
    const Tweets = [];
    fetch('http://localhost:8081/search/dog')
    .then(e=>e.json())
    .then(twit => {
      twit.statuses.forEach((el, i) => {
        Tweets.push(<Tweet
          key={i}
          user={el.user.name}
          content={el.text}
          translate={this.translate}
          saveTweet={this.saveTweet}
        ></Tweet>);

        this.setState({tweets:Tweets});
      });
    })
    .catch(console.log)

    window.gapi.load('client', this.start);
  }

  translate(content, func) {
    if(this.state.translate != null) {
      this.state.translate({
        q: content,
        source: 'en',
        target: this.state.lang,
      }).then(e => {
        const trans = JSON.parse(e.body).data.translations[0].translatedText
        func(trans);
      });
    }
  }

  saveTweet(user, content, translatedContent) {
    console.log("sdg")
  }

  start() {
    // Initializes the client with the API key and the Translate API.
    window.gapi.client.init({
      'apiKey': 'AIzaSyA1wznaFOnhsj0ZX14zgIhrLC6wkmsS8X8',
      'discoveryDocs': ['https://www.googleapis.com/discovery/v1/apis/translate/v2/rest'],
    }).then( () => {
      this.setState({ translate: window.gapi.client.language.translations.translate});
    });
  }

  render() {
    return (
      <div className="container">
        <div className="input-field col s6"> 
          <i style={iStyle} className="material-icons prefix">search</i>
          <input id="icon_telephone" type="tel" className="validate"></input>
            <label htmlFor="icon_telephone">Tweets</label>
        </div>
        <div className="input-field col s6">
          <i style={iStyle} className="material-icons prefix">search</i>
          <input id="icon_telephone" type="tel" className="validate"></input>
          <label htmlFor="icon_telephone">Users</label>
        </div>
        <ul className="collection">
          {this.state.tweets}
        </ul>
      </div>
    );
  }
}

export default Search;