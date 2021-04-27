import React, { Component } from 'react';
import PropTypes from 'prop-types';

const propTypes = {
  children: PropTypes.node,
};

const defaultProps = {};

class FrontEndFooter extends Component {
  constructor(props) {
    super(props);
    this.state = {
      url: 'https://xtblock.io/',
    };
  }

  render() {
    // eslint-disable-next-line
    const { children, ...attributes } = this.props;

    return (
      <React.Fragment>
        <span>
          <a href={this.state.url}>© YouRoot Pte. Ltd.</a> 2020
        </span>
        <span className="ml-auto">
          Powered by <a href="https://xtblock.io/">xtblock.io</a>
        </span>
      </React.Fragment>
    );
  }
}

FrontEndFooter.propTypes = propTypes;
FrontEndFooter.defaultProps = defaultProps;

export default FrontEndFooter;
