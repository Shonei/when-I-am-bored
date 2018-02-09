import React, { Component } from 'react';

const iStyle = {
  cursor: 'pointer'
};

class Tweet extends Component {
  constructor(props) {
    super(props);

    this.state = {
      translatedBody: null,
      icon: 'q_translate',
      translated: null,
      action: this.props.translate
    };

    this.handleClick = this.handleClick.bind(this);
    this.translated = this.translated.bind(this);
  }

  translated(text) {
    this.setState({ translated: text });
    const body = <p><b>Translated: </b>{text}</p>;
    this.setState({ translatedBody: body });
    this.setState({ action: this.props.saveTweet });
    this.setState({ icon: 'save' });
  }

  handleClick(e) {
    if (this.state.translated === null) {
      this.state.action(this.props.content, this.translated);
    } else {
      this.state.action(this.props.user, this.props.content, this.state.translated);
    }
  }

  render() {
    return (
      <div>
        <li className="collection-item avatar">
          <a onClick={this.handleClick}><i style={iStyle} className="material-icons circle">{this.state.icon}</i></a>
          <span className="title"><b>User:</b> {this.props.user}</span>
          <p><b>Content: </b>{this.props.content}</p>
          {this.state.translatedBody}
        </li>
      </div>
    );
  }
}

export default Tweet;