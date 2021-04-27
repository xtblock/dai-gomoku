import React, { Component } from 'react';
import PropTypes from 'prop-types';

const propTypes = {
  children: PropTypes.node,
};

const defaultProps = {};

class DefaultFooter extends Component {
  constructor(props) {
    super(props);
    this.state = {
      url: '',
    };
  }

  render() {
    // eslint-disable-next-line
    const { children, ...attributes } = this.props;

    return (
      <React.Fragment>
        <span>
          <a href={this.state.url}>CoreUI</a> &copy; 2019 creativeLabs.
        </span>
        <span className="ml-auto">
          Powered by <a href="https://coreui.io/react">CoreUI for React</a>
        </span>
      </React.Fragment>
    );
  }
}

DefaultFooter.propTypes = propTypes;
DefaultFooter.defaultProps = defaultProps;

export default DefaultFooter;
