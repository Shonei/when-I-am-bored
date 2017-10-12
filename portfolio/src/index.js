import React from 'react';
import ReactDOM from 'react-dom';
import './Navbar.css';
import Navbar from './Navbar';
import registerServiceWorker from './registerServiceWorker';

ReactDOM.render(<Navbar />, document.getElementById('root'));
registerServiceWorker();
