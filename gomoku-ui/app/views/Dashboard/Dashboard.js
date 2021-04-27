import React, { Component } from 'react';

class Dashboard extends Component {
  constructor(props) {
    super(props);
    this.state = {
      dropdownOpen: false,
    };
  }

  render() {
    return (
      <div className="animated fadeIn">
        <h1>{this.state.dropdownOpen}</h1>
      </div>
    );
  }
}

export default Dashboard;
