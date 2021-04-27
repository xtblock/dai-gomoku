import React, { PureComponent, Component } from 'react';
import PropTypes from 'prop-types';

class Square extends Component {

  constructor(props) {
    super(props);
    this.state = {
      checkColor: '',
      intervalId: null,
    };
  }

  componentDidMount() {

    //var intervalId = setInterval(this.timer(self), 1000);
    var intervalId = setInterval(() => {
      this.setState({ checkColor: this.state.checkColor ? "" : "check" });
      console.log("Here123");
    }, 1000);
    // store intervalId in the state so it can be accessed later:
    this.setState({ intervalId: intervalId });

  }

  componentWillUnmount() {
    //if (this.isInCheckList()) {
    // use intervalId from the state to clear the interval
    clearInterval(this.state.intervalId);
    //}
  }

  handleClick = () => {
    const { x, y, onClick } = this.props;
    onClick(x, y);
  }

  isInCheckList = () => {
    const { x, y, checkList } = this.props;
    let isIn = false;
    checkList.map(check => {
      if (check.x == x && check.y == y) {
        isIn = true;
      }
    });

    return isIn;
  }

  timer = () => {
    // setState method is used to update the state
    this.setState({ checkColor: this.state.checkColor ? "" : "check" });
    console.log(this.state.checkColor);
  }

  render() {
    const { value, width, height, x, y, latestX, latestY, checkList } = this.props;
    let stoneColor = '';
    if (value) {
      stoneColor = value === 1 ? 'black' : 'white';
    } else {
      if (this.isInCheckList()) {
        stoneColor = this.state.checkColor;
      }
    }
    return (
      <button
        type="button"
        className="board-row__square"
        onClick={this.handleClick}
        style={{ width: width, height: height }}
      >
        <span className={`board-row__stone board-row__stone--${stoneColor} ${x == latestX && y == latestY ? `latest-move-${stoneColor}` : ''}`} />
      </button>
    );
  }
}

Square.defaultProps = {
  value: null,
};

Square.propTypes = {
  x: PropTypes.number.isRequired,
  y: PropTypes.number.isRequired,
  latestX: PropTypes.number.isRequired,
  latestY: PropTypes.number.isRequired,
  value: PropTypes.number,
  onClick: PropTypes.func.isRequired,
  width: PropTypes.number.isRequired,
  height: PropTypes.number.isRequired,
};

export default Square;
