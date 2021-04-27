import React, { Component, Suspense } from 'react';
// import { Redirect, Route, Switch } from 'react-router-dom';
import * as router from 'react-router-dom';
import { Container } from 'reactstrap';
import PropTypes from 'prop-types';
import {
  AppAside,
  AppFooter,
  AppHeader,
  AppSidebar,
  AppSidebarFooter,
  AppSidebarForm,
  AppSidebarHeader,
  AppSidebarMinimizer,
  AppBreadcrumb2 as AppBreadcrumb,
  AppSidebarNav2 as AppSidebarNav,
} from '@coreui/react';


import { connect } from 'react-redux';
import { compose } from 'redux';
import { createStructuredSelector } from 'reselect';
import injectReducer from 'utils/injectReducer';
import injectSaga from 'utils/injectSaga';

import reducer from './reducer';
import saga from './saga';

import {
  makeSelectAdminLoginResult,
} from 'containers/App/selectors';

// sidebar nav config
import navigation from '../_nav';
// routes config
import adminRoutes from '../../adminRoutes';

const DefaultAside = React.lazy(() => import('./DefaultAside'));
const DefaultFooter = React.lazy(() => import('./DefaultFooter'));
const DefaultHeader = React.lazy(() => import('./DefaultHeader'));

class DefaultLayout extends Component {
  constructor(props) {
    super(props);
    this.state = {
      username: "",
      password: "",

      errorMessageCode: "",

      isAttemptingLogin: false,
      loginSuccess: false,
    };
  }

  componentDidMount() {
    const { adminLoginResult } = this.props;
    if (adminLoginResult && adminLoginResult.data && adminLoginResult.data.userType == 'admin') {
      //alert(JSON.stringify(adminLoginResult));
    } else {
      this.props.history.push('/admin-login');
    }
  }

  componentDidUpdate(prevProps, prevState) {

  }

  loading = () => (
    <div className="animated fadeIn pt-1 text-center">Loading...</div>
  );

  signOut(e) {
    e.preventDefault();
    this.props.history.push('/login');
  }

  render() {
    return (
      <div className="app">
        <AppHeader fixed>
          <Suspense fallback={this.loading()}>
            <DefaultHeader onLogout={e => this.signOut(e)} />
          </Suspense>
        </AppHeader>
        <div className="app-body">
          <AppSidebar fixed display="lg">
            <AppSidebarHeader />
            <AppSidebarForm />
            <Suspense>
              <AppSidebarNav
                navConfig={navigation}
                {...this.props}
                router={router}
              />
            </Suspense>
            <AppSidebarFooter />
            <AppSidebarMinimizer />
          </AppSidebar>
          <main className="main">
            <AppBreadcrumb appRoutes={adminRoutes} router={router} />
            <Container fluid>
              <Suspense fallback={this.loading()}>
                <router.Switch>
                  {adminRoutes.map((route, idx) => {
                    const key = `route_${idx}`;
                    if (route.component) {
                      return (
                        <router.Route
                          key={key}
                          path={route.path}
                          exact={route.exact}
                          name={route.name}
                          render={props => <route.component {...props} />}
                        />
                      );
                    }
                    return null;
                  })}
                  <router.Redirect from="/admin" to="/admin/dashboard" />
                </router.Switch>
              </Suspense>
            </Container>
          </main>
          <AppAside fixed>
            <Suspense fallback={this.loading()}>
              <DefaultAside />
            </Suspense>
          </AppAside>
        </div>
        <AppFooter>
          <Suspense fallback={this.loading()}>
            <DefaultFooter />
          </Suspense>
        </AppFooter>
      </div>
    );
  }
}

DefaultLayout.propTypes = {
  history: PropTypes.object,
};


export function mapDispatchToProps(dispatch) {
  return {

  };
}

const mapStateToProps = createStructuredSelector({
  adminLoginResult: makeSelectAdminLoginResult(),
});

const withConnect = connect(
  mapStateToProps,
  mapDispatchToProps,
);

const withReducer = injectReducer({ key: 'defaultLayout', reducer });
const withSaga = injectSaga({ key: 'defaultLayout', saga });

export default compose(
  withReducer,
  withSaga,
  withConnect,
)(DefaultLayout);
