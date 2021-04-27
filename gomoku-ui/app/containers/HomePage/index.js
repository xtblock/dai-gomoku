/*
 * HomePage
 *
 * This is the first thing users see of our App, at the '/' route
 *
 */

import React, { Component } from 'react';

import { FormattedMessage } from 'react-intl';
import socketIOClient from "socket.io-client";

import {
  Button,
  ButtonGroup,
  Card,
  CardBody,
  Carousel,
  CarouselCaption,
  CarouselControl,
  CarouselIndicators,
  CarouselItem,
  Col,
  Row,
  Form,
  Radio,
  Input
} from 'reactstrap';

import Particles from 'react-particles-js';
import AspectRatio from 'react-aspect-ratio';
import PropTypes from 'prop-types';
import { connect } from 'react-redux';
import { compose } from 'redux';
import { createStructuredSelector } from 'reselect';

import injectReducer from 'utils/injectReducer';
import injectSaga from 'utils/injectSaga';

import {
  makeSelectGetPortfolioListResult,
  makeSelectLoadingGetPortfolioList,
  makeSelectErrorGetPortfolioList,
} from 'containers/App/selectors';

import { getPortfolioList } from '../App/actions';

import {
  changeStatus,
  changeKeyword,
  changePageNumber,
  changeNumberPerPage,
} from './actions';

import {
  makeSelectStatus,
  makeSelectKeyword,
  makeSelectPageNumber,
  makeSelectNumberPerPage,
} from './selectors';
import reducer from './reducer';
import saga from './saga';

import { AppAsideToggler, AppNavbarBrand } from '@coreui/react';

import Board from 'components/gomoku/Board';
import logo from '../../assets/img/brand/logo.png';
//import 'reset.css';
import 'scss/index.scss';

const ENDPOINT = "http://127.0.0.1:4000";

const calculateWinner = (squares, x, y, player) => {
  const num = 5;
  const calcuNum = (dx, dy) => {
    let i;
    for (i = 1; i < num; i++) {
      if (!squares[y + dy * i] || !squares[y + dy * i][x + dx * i]
        || player !== squares[y + dy * i][x + dx * i]) return i - 1;
    }
    return i;
  };

  const checkDirec = (first, second) => {
    const firstN = calcuNum(first.x, first.y);
    const secondN = calcuNum(second.x, second.y);
    return (secondN === num || firstN === num
      || (secondN + firstN) >= num - 1)
      ? player : null;
  };

  const directions = [
    { fist: { x: -1, y: 0 }, second: { x: 1, y: 0 } },
    { fist: { x: 0, y: 1 }, second: { x: 0, y: -1 } },
    { fist: { x: -1, y: -1 }, second: { x: 1, y: 1 } },
    { fist: { x: -1, y: 1 }, second: { x: 1, y: -1 } },
  ];

  const isWinner = directions.find(direction => checkDirec(direction.fist, direction.second));

  if (isWinner) return player;
  return null;
};


const calculateCheck = (squares, x, y, player) => {
  //console.log(squares);
  const num = 4;
  let checkList = [];
  const calcuNum = (dx, dy) => {
    let i;
    for (i = 1; i < num; i++) {
      if (!squares[y + dy * i] || !squares[y + dy * i][x + dx * i]
        || player !== squares[y + dy * i][x + dx * i]) return i - 1;
    }
    console.log(y + dy * (i - 1));
    console.log(x + dx * (i - 1));

    return i;
  };

  const checkDirec = (first, second) => {
    const firstN = calcuNum(first.x, first.y);
    const secondN = calcuNum(second.x, second.y);
    /*
    return (secondN === num || firstN === num
      || (secondN + firstN) >= num - 1)
      ? player : null;
      */

    if (firstN === num) {
      //checkList.push({ x: X, y: Y });
      if (first.x == -1 && first.y == 0) {
        console.log("HERE 1..............");
        checkList.push({ x: x + 1, y });
        checkList.push({ x: x - num, y });
      }

      if (first.x == 0 && first.y == 1) {
        console.log("HERE 2..............");
        checkList.push({ x: x, y: y - 1 });
        checkList.push({ x: x, y: y + num });
      }

      if (first.x == -1 && first.y == -1) {
        console.log("HERE 3..............");
        checkList.push({ x: x + 1, y: y + 1 });
        checkList.push({ x: x - num, y: y - num });
      }

      if (first.x == -1 && first.y == 1) {
        console.log("HERE 4..............");
        checkList.push({ x: x + 1, y: y + 1 });
        checkList.push({ x: X - num, y: Y - num });
      }
    } else if (secondN === num) {
      console.log("HERE 5..............");
      if (second.x == 1 && second.y == 0) {
        checkList.push({ x: x - 1, y: y });
        checkList.push({ x: x + num, y: y });
      }

      if (second.x == 0 && second.y == -1) {
        console.log("HERE 6..............");
        checkList.push({ x: x, y: y + 1 });
        checkList.push({ x: x, y: y - num });
      }

      if (second.x == 1 && second.y == 1) {
        console.log("HERE 7..............");
        checkList.push({ x: x - 1, y: y - 1 });
        checkList.push({ x: x + num, y: y + num });
      }

      if (second.x == 1 && second.y == -1) {
        console.log("HERE 8..............");
        checkList.push({ x: x - 1, y: y + 1 });
        checkList.push({ x: x + num, y: y - num });
      }
    }
  };

  const directions = [
    { fist: { x: -1, y: 0 }, second: { x: 1, y: 0 } },
    { fist: { x: 0, y: 1 }, second: { x: 0, y: -1 } },
    { fist: { x: -1, y: -1 }, second: { x: 1, y: 1 } },
    { fist: { x: -1, y: 1 }, second: { x: 1, y: -1 } },
  ];

  directions.map(direction => checkDirec(direction.fist, direction.second));

  return checkList;
  /*
  const isWinner = directions.find(direction => checkDirec(direction.fist, direction.second));
  console.log(checkList);
  console.log(isWinner);
  if (isWinner) return player;
  return null;
  */
};

const NextStone = ({ oneIsNext }) => (
  <div className="player">
    <p className="player__info">Next</p>
    <div className="player__shadow">
      <div className={`player__stone player__stone-${oneIsNext ? 'black' : 'white'}`} />
    </div>
  </div>
);

NextStone.propTypes = {
  oneIsNext: PropTypes.bool.isRequired,
};

const WinnerStone = ({ isBlack }) => (
  <div className="player player-winner">
    <p className="player__info">Winner</p>
    <div className="player__shadow">
      <div className={`player__stone player__stone-${isBlack ? 'black' : 'white'}`} />
    </div>
  </div>
);

WinnerStone.propTypes = {
  isBlack: PropTypes.bool.isRequired,
};

let socket = null;

// export default function HomePage() {
class HomePage extends Component {

  constructor(props) {
    super(props);
    this.state = {
      history: [{
        squares: Array(19).fill().map(() => Array(19).fill(null)),
        //squares: Array(10).fill().map(() => Array(10).fill(null)),
      }],
      stepNumber: 0,
      oneIsNext: true,
      winner: null,
      checkList: [],
      custom: {
        x: '',
        y: '',
      },
      isNewGame: true,
      isGameStart: false,
      userColorNumber: 1,
      boardWidth: 0,
      latestX: 0,
      latestY: 0,
    };
  }


  handleClick = (x, y) => {
    this.makeAMove(x, y, false);
    /*
    this.sendData({ x: x, y: y });
    const { isGameStart, oneIsNext, userColorNumber } = this.state;
    if (this.state.isGameStart && ((oneIsNext == userColorNumber) || (!oneIsNext && (userColorNumber == 2)))) {
      const { oneIsNext, stepNumber, winner } = this.state;
      let { history } = this.state;
      history = history.slice(0, stepNumber + 1);
      const current = history[history.length - 1];
      const squares = JSON.parse(JSON.stringify(current.squares.slice()));
      if (winner || squares[y][x]) {
        return;
      }

      squares[y][x] = oneIsNext ? 1 : 2;
      this.setState({
        history: history.concat([{ squares }]),
        stepNumber: history.length,
        oneIsNext: !oneIsNext,
        winner: calculateWinner(squares, x, y, squares[y][x]),
      });
    }
    */
  }

  makeAMove = (x, y, isAI) => {
    const { isGameStart, oneIsNext, stepNumber, winner, userColorNumber, checkList } = this.state;
    if (!isAI) {
      if (!isGameStart || (oneIsNext && userColorNumber == 2) || (!oneIsNext && userColorNumber == 1)) {
        //return;
      }
    }

    if (isAI) {
      this.setState({
        latestX: x,
        latestY: y
      });
    } else {
      this.setState({
        latestX: x,
        latestY: y
      });
    }

    let { history } = this.state;
    history = history.slice(0, stepNumber + 1);
    const current = history[history.length - 1];
    const squares = JSON.parse(JSON.stringify(current.squares.slice()));
    if (winner || squares[y][x]) {
      this.sendData({ "x": x, "y": 18 - y, "player": oneIsNext ? 1 : -1 });
      return;
    }

    squares[y][x] = oneIsNext ? 1 : 2;

    let isWon = calculateWinner(squares, x, y, squares[y][x]);
    this.setState({
      history: history.concat([{ squares }]),
      stepNumber: history.length,
      oneIsNext: !oneIsNext,
      winner: calculateWinner(squares, x, y, squares[y][x]),
      checkList: isWon ? [] : [...checkList, ...calculateCheck(squares, x, y, squares[y][x])],
    });
    if (!isAI) {
      //console.log(squares);
      this.sendData({ "x": x, "y": 18 - y, "player": oneIsNext ? 1 : -1 });
    }
  }

  handleClickNewGame = () => {
    this.setState({
      isNewGame: true,
      isGameStart: false,
    });
  }

  handleClickStartGame = () => {
    this.setState({
      winner: null,
      checkList: [],
      isNewGame: false,
      isGameStart: true,
      history: [{
        squares: Array(19).fill().map(() => Array(19).fill(null)),
      }],
      stepNumber: 0,
      oneIsNext: true,
    });

    if (this.state.userColorNumber == 2) {
      this.sendData({ "x": -1, "y": -1, "player": -1, "status": "start" });
    }
  }

  handleSelectColor = (colorNumber) => {
    this.setState({
      userColorNumber: colorNumber
    })
  }


  static getDerivedStateFromProps(nextProps, prevState) {

    return null;
  }

  componentDidMount() {
    let self = this;
    socket = socketIOClient(ENDPOINT);
    socket.on("dAIMove", function (data) {
      console.log(data);
      self.makeAMove(data.x, 18 - data.y, true);
    });

    const width = document.getElementById('board-container').clientWidth;
    this.setState({
      boardWidth: width
    })

    window.addEventListener('resize', this.updateDimensions);

  }

  componentDidUpdate(prevProps, prevState) {

  }

  componentWillUnmount() {
    window.removeEventListener('resize', this.updateDimensions);
  }

  updateDimensions = () => {
    const width = document.getElementById('board-container').clientWidth;
    this.setState({
      boardWidth: width
    })
  };

  sendData = (data) => {
    socket.emit("userMove", data);
  }

  render() {

    const indexArr = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's'];
    /*
    for (var i = 1; i < 20; i++) {
      indexArr.push(i);
    }
    */
    const indexArrY = [];
    for (var i = 19; i > 0; i--) {
      indexArrY.push(i);
    }

    const {
      history, stepNumber, oneIsNext, winner, checkList, custom: { x, y }, isNewGame, isGameStart, boardWidth
    } = this.state;
    const current = history[stepNumber];
    const whichsize = x ? 'custom' : history[0].squares.length;

    return (
      <div className="homepage-wrapper">
        <Row className="mr-0 ml-0">
          <Col xs="12" xl="3">
            <div className="text-center mt-5">
              <AppNavbarBrand
                className="mr-0"
                full={{
                  src: logo,
                  width: 200,
                  height: 50,
                  alt: "XTBlock Logo",
                }}
              />
            </div>
            <h1 className="game_title text-center">Gomoku</h1>
            <Row >
              <Col xs="6" xl="6" className="text-right">
                <h4><span className="contestant">Players</span></h4>
                <h1><span className="contestant-result">6</span></h1>
              </Col>
              <Col xs="6" xl="6" className="text-left">
                <h4><span className="contestant">dAI</span></h4>
                <h1><span className="contestant-result">9</span></h1>
              </Col>
            </Row>
            <div className="d-none d-xl-block">
              <br />
              <br />
              <p className="text-center copy-right">XTblock's dAI Framework v0.5</p>
            </div>
          </Col>

          <Col xs="12" xl="3" className="d-xl-none text-center">
            {!isNewGame ?
              (
                <Button type="submit" color="primary" className="button-background" onClick={this.handleClickNewGame}>
                  New Game
                </Button>) : null}
            {!isNewGame ? (
              <div className="text-center">
                {winner && <WinnerStone isBlack={winner === 1} />}
                {!winner && <NextStone oneIsNext={oneIsNext} />}
              </div>) : null}

            {isNewGame ? (
              <div className="mb-2">
                <h3>Select your color:</h3>
                <Row className="mb-2">
                  <Col xs="12" xl="4" className="text-center">
                    <Row className="select-color-option1 text-center">
                      <Col className="text-right pt-2">
                        <Input ref="input1" type="radio" name="radioButtonSet" value='input1' standalone defaultChecked onClick={() => { this.handleSelectColor(1) }} />
                      </Col>
                      <Col className="text-left">
                        <div className="player__shadow"><div className={`player__stone player__stone-black`} /></div>
                      </Col>
                    </Row>
                  </Col>
                  <Col xs="12" xl="4" className="mt-2">
                    <Row className="select-color-option1 text-center">
                      <Col className="text-right pt-2">
                        <Input ref="input2" type="radio" name="radioButtonSet" value='input2' standalone onClick={() => { this.handleSelectColor(2) }} />
                      </Col>
                      <Col className="text-left">
                        <div className="player__shadow"><div className={`player__stone player__stone-white`} /></div>
                      </Col>
                    </Row>

                  </Col>
                </Row>
                <Button type="submit" color="primary" className="button-background" onClick={this.handleClickStartGame}>
                  Start Game
                        </Button>
              </div>) : null}

          </Col>
          <Col xs="12" xl="6" className="mt-1">
            <Row>
              <Col xs="1" xl="1" className="text-right pl-0 pr-0">
                <div className="vertical-index-wrapper">
                  {indexArrY.map(i => (
                    <div className="vertical-index" style={{ height: boardWidth / 19 - 1 }}><span style={{ fontSize: 12 }}>{i}</span></div>
                  ))
                  }
                </div>
              </Col>

              <Col xs="11" xl="11" id="board-container" className="text-center pr-0 pl-0">

                <Board
                  width={this.state.boardWidth / 19}
                  height={this.state.boardWidth / 19}
                  latestX={this.state.latestX}
                  latestY={this.state.latestY}
                  squares={current.squares}
                  checkList={checkList}
                  onClick={this.handleClick}
                />
                <div className="horizontal-index-wrapper">
                  {indexArr.map(i => (
                    <span className="horizontal-index" style={{ width: boardWidth / 19 }}>{i.toUpperCase()}</span>
                  ))
                  }
                </div>
              </Col>
            </Row>

          </Col>
          <Col xs="12" xl="3" className="d-none d-xl-block">
            <Card className="border-0 bg-transparent">
              <CardBody>
                <div className="mt-5">
                  {winner && <WinnerStone isBlack={winner === 1} />}
                  {!winner && <NextStone oneIsNext={oneIsNext} />}
                </div>
                {!isNewGame ?

                  (
                    <Button type="submit" color="primary" className="button-background" onClick={this.handleClickNewGame}>
                      New Game
                    </Button>) : null}
                {isNewGame ? (
                  <div className="">
                    <br />
                    <h3>Select your color:</h3>
                    <Row className="mb-5">
                      <Col xs="12" xl="4" className="text-center">
                        <div className="text-center">
                          <Input ref="input1" type="radio" name="radioButtonSet" value='input1' standalone defaultChecked onClick={() => { this.handleSelectColor(1) }} />
                          <br />
                          <br />
                          <div className="player__shadow"><div className={`player__stone player__stone-black`} /></div>
                        </div>
                      </Col>
                      <Col xs="12" xl="4" className="text-left">
                        <div className="text-center">        <Input ref="input2" type="radio" name="radioButtonSet" value='input2' standalone onClick={() => { this.handleSelectColor(2) }} />
                          <br />
                          <br />
                          <div className="player__shadow"><div className={`player__stone player__stone-white`} /></div>
                        </div>

                      </Col>
                    </Row>
                    <Button type="submit" color="primary" className="button-background" onClick={this.handleClickStartGame}>
                      Start Game
                        </Button>
                  </div>) : null}
              </CardBody>
            </Card>
          </Col>

        </Row>
        <div className="d-xl-none text-center">
          <br /><br />
          <p className="text-center copy-right">XTblock's dAI Framework v0.5</p>
        </div>
      </div>
    );
  }
}

export function mapDispatchToProps(dispatch) {
  return {
    onChangeStatus: status => dispatch(changeStatus(status)),
    onChangeKeyword: keyword => dispatch(changeKeyword(keyword)),
    onChangePageNumber: pageNumber => dispatch(changePageNumber(pageNumber)),
    onChangeNumberPerPage: numberPerPage => dispatch(changeNumberPerPage(numberPerPage)),

    onGetPortfolioList: evt => {
      if (evt !== undefined && evt.preventDefault) evt.preventDefault();
      dispatch(getPortfolioList());
    },
  };
}

const mapStateToProps = createStructuredSelector({
  status: makeSelectStatus(),
  keyword: makeSelectKeyword(),
  pageNumber: makeSelectPageNumber(),
  numberPerPage: makeSelectNumberPerPage(),

  getPortfolioListResult: makeSelectGetPortfolioListResult(),
  loading: makeSelectLoadingGetPortfolioList(),
  error: makeSelectErrorGetPortfolioList(),
});

const withConnect = connect(
  mapStateToProps,
  mapDispatchToProps,
);

const withReducer = injectReducer({ key: 'home', reducer });
const withSaga = injectSaga({ key: 'home', saga });

export default compose(
  withReducer,
  withSaga,
  withConnect,
)(HomePage);
