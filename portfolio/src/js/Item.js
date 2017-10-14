import React, { Component } from 'react';

class Item extends Component {
  constructor(props) {
    super(props);
    this.content = <div></div>;
    this.handleClick = null;

    if(this.props.onclick) {
      this.handleClick = this.props.onclick;
    }

    if(this.props.content) {
      this.content = <div className="card-content"><p>{this.props.content}</p></div>;
    } 
  }

  render() {
    return (
      <div id="item">
        <div className="card">
          <div className="card-image">
            <img src={this.props.img} alt={this.props.title}/>
          </div>
          {this.content}
          <div className="card-action">
            <a href={this.props.URL} 
              onClick={this.handleClick}>
              {this.props.title}
            </a>
          </div>
        </div>
      </div>
    );
  }
}

export default Item;