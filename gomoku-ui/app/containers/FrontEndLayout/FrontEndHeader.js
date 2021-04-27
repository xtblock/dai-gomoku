import React, { Component } from 'react';
import { NavLink } from 'react-router-dom';
import PropTypes from 'prop-types';
import {
  UncontrolledDropdown,
  DropdownItem,
  DropdownMenu,
  DropdownToggle,
  Nav,
  NavItem,
} from 'reactstrap';
import { AppAsideToggler, AppNavbarBrand } from '@coreui/react';
import logo from '../../assets/img/brand/logo.png';
import sygnet from '../../assets/img/brand/sygnet.svg';

const propTypes = {
  children: PropTypes.node,
};

const defaultProps = {};

class FrontEndHeader extends Component {
  constructor(props) {
    super(props);
    this.state = {
      alt: 'XTBlock Logo',
    };
  }

  activeRoute(routeName) {
    return this.props.location.pathname.indexOf(routeName) > -1
      ? 'nav-link active'
      : 'nav-link';
  }

  render() {
    // eslint-disable-next-line
    const { children, ...attributes } = this.props;

    return (
      <React.Fragment>
        <AppNavbarBrand
          full={{
            src: logo,
            width: 100,
            height: 25,
            alt: this.state.alt,
          }}
          minimized={{
            src: sygnet,
            width: 30,
            height: 30,
            alt: 'MonNa Logo',
          }}
        />
        <Nav className="d-md-down-none ml-auto front-end-menu" navbar>
           {/*
          <NavItem className="px-3">
            <NavLink to="/home" className={this.activeRoute('home')}>
              Home
            </NavLink>
          </NavItem>



          <NavItem className="px-3">
            <NavLink
              to="/register-ip"
              className={this.activeRoute('register-ip')}
            >
              Register IP
            </NavLink>
          </NavItem>
          */}
        </Nav>
        <Nav className="ml-auto" navbar>
          <UncontrolledDropdown className="d-lg-none" nav direction="down">
            <DropdownToggle nav>
              <AppAsideToggler className="d-lg-none" />
            </DropdownToggle>
            <DropdownMenu right>
               {/*
              <DropdownItem>
                <NavLink to="/home" className="nav-link">
                  <i className="fa fa-home" /> Home
                </NavLink>
              </DropdownItem>



              <DropdownItem>
                <NavLink to="/register-ip" className="nav-link">
                  <i className="fa fa-id-card" /> Register IP
                </NavLink>
              </DropdownItem>
               */}
            </DropdownMenu>
          </UncontrolledDropdown>
        </Nav>
      </React.Fragment>
    );
  }
}

FrontEndHeader.propTypes = propTypes;
FrontEndHeader.defaultProps = defaultProps;

FrontEndHeader.propTypes = {
  location: PropTypes.object,
};

export default FrontEndHeader;
