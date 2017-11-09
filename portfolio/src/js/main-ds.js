import React, { Component } from 'react';
import Search from './Search';
import Saved from './Saved';

const a = {
    // lineHeight: '1em',
    // display: 'inline - block',
    // textDecoration: 'none',
    // padding: '2px',
    margin: '2px'
};

class MainDs extends Component {
  constructor(props) {
    super(props);

    this.state = {
      body: <Search></Search>
    };
  }

  render() {
    return (
      <div>
        <br/>
        <div>
          <a style={a} onClick={()=>this.setState({body:<Search></Search>})} className="waves-effect waves-light btn">Search</a>
          <a style={a} onClick={()=>this.setState({body:<Saved></Saved>})} className="waves-effect waves-light btn">Saved</a>
          <a style={a} className="dropdown-button btn" data-activates="lang">Language</a>
          <div>
            <ul id="lang" className="dropdown-content">
              <li><a value="bg" onClick={e => console.log(e.target.getAttribute('value'))}>Bulgarian</a></li>
              <li><a>Spanish</a></li>
              <li className="divider"></li>
            </ul>
          </div>
        </div>
        {this.state.body}
      </div>
    );
  }
}

export default MainDs;