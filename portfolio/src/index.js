import React from 'react';
import ReactDOM from 'react-dom';
import * as firebase from "firebase";
import Navbar from './js/Navbar';
import registerServiceWorker from './js/registerServiceWorker';

const config = {
    apiKey: "AIzaSyA1wznaFOnhsj0ZX14zgIhrLC6wkmsS8X8",
    authDomain: "shonei-portfolio.firebaseapp.com",
    databaseURL: "https://shonei-portfolio.firebaseio.com",
    projectId: "shonei-portfolio",
    storageBucket: "shonei-portfolio.appspot.com",
    messagingSenderId: "199550501764"
};

firebase.initializeApp(config);

ReactDOM.render(<Navbar firebase={firebase} />, document.getElementById('root'));
registerServiceWorker();
