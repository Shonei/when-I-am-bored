import React, { Component } from 'react';
import Tweet from './Tweet';
import fetch from 'node-fetch';

const iStyle = {
  cursor: 'pointer'
};

class Search extends Component {
  constructor(props) {
    super(props);

    this.state = {
      translate: null,
      lang: 'bg',
      tweets: [],
      searchTweets: '',
      searchUser: '',
      language: 'Bulgarian'
    };

    this.start = this.start.bind(this);
    this.translate = this.translate.bind(this);
    this.saveTweet = this.saveTweet.bind(this);
    this.renderTweets = this.renderTweets.bind(this);
    this.search = this.search.bind(this);
  }

  componentDidMount() {
    window.gapi.load('client', this.start);
  }

  renderTweets(twit) {
    if (twit.length < 1) {
      return;
    }

    const Tweets = [];
    if (twit.statuses) {
      twit = twit.statuses;
    }

    twit.forEach((el, i) => {
      Tweets.push(<Tweet
        key={i}
        user={el.user.name}
        content={el.text}
        translate={this.translate}
        saveTweet={this.saveTweet}
      ></Tweet>);

      this.setState({ tweets: Tweets });
    });
  }

  search(url) {
    fetch(url)
      .then(e => e.json())
      .then(this.renderTweets)
      .catch(console.log)
  }

  translate(content, func) {
    if (this.state.translate != null) {
      this.state.translate({
        q: content,
        source: 'en',
        target: this.state.lang,
      }).then(e => {
        const trans = JSON.parse(e.body).data.translations[0].translatedText;
        func(trans);
      });
    }
  }

  saveTweet(user, content, translatedContent) {
    const tweets = this.props.database.ref('/tweets');
    const newTweet = tweets.push();
    newTweet.set({
      uname: String(user),
      original: String(content),
      translated: String(translatedContent)
    });
  }

  start() {
    window.gapi.client.init({
      'apiKey': 'AIzaSyA1wznaFOnhsj0ZX14zgIhrLC6wkmsS8X8',
      'discoveryDocs': ['https://www.googleapis.com/discovery/v1/apis/translate/v2/rest'],
    }).then(() => {
      this.setState({ translate: window.gapi.client.language.translations.translate });
    });
  }

  render() {
    return (
      <div className="container">
        <div className="input-field col s6">
          <i onClick={e => this.search('https://website-6de1e.appspot.com/search/' + this.state.searchTweets)}
            style={iStyle} className="material-icons prefix">search</i>
          <input onChange={e => this.setState({ searchTweets: e.target.value })}
            id="icon_telephone" type="search" className="validate"></input>
          <label htmlFor="icon_telephone">Tweets</label>
        </div>
        <div className="input-field col s6">
          <i onClick={e => this.search('https://website-6de1e.appspot.com/user/' + this.state.searchUser)}
            style={iStyle} className="material-icons prefix">search</i>
          <input onChange={e => this.setState({ searchUser: e.target.value })}
            id="icon_telephone" type="search" className="validate"></input>
          <label htmlFor="icon_telephone">Users</label>
        </div>
        <a className="dropdown-button btn" data-activates="lang"><i className="material-icons right">arrow_drop_down</i>Language</a>
        <p><b>{this.state.language}</b></p>
        <div>
          <ul id="lang" className="dropdown-content">
            <li><a val="bg" onClick={e => this.setState({
              language: e.target.textContent, lang: e.target.getAttribute('val')
            })}
            >Bulgarian</a></li>
            <li><a val="fr" onClick={e => this.setState({
              language: e.target.textContent, lang: e.target.getAttribute('val')
            })}
            >French</a></li>
            <li><a val="de" onClick={e => this.setState({
              language: e.target.textContent, lang: e.target.getAttribute('val')
            })}
            >German</a></li>
            <li><a val="ja" onClick={e => this.setState({
              language: e.target.textContent, lang: e.target.getAttribute('val')
            })}
            >Japanese</a></li>
            <li><a val="ru" onClick={e => this.setState({
              language: e.target.textContent, lang: e.target.getAttribute('val')
            })}
            >Russian</a></li>
            <li><a val="es" onClick={e => this.setState({
              language: e.target.textContent, lang: e.target.getAttribute('val')
            })}
            >Spanish</a></li>
            <li className="divider"></li>
          </ul>
        </div>
        <ul className="collection">
          {this.state.tweets}
        </ul>
      </div>
    );
  }
}

export default Search;