import React, { PureComponent } from 'react';
import PropTypes from 'prop-types';
import Square from './Square';
import 'scss/Board.scss';

class Board extends PureComponent {
  renderSquare(x, y) {
    const { squares, checkList, onClick, width, height, latestX, latestY } = this.props;
    return (
      <Square
        key={`${x}-${y}`}
        x={x}
        y={y}
        latestX={latestX}
        latestY={latestY}
        value={squares[y][x]}
        onClick={onClick}
        width={width}
        height={height}
        checkList={checkList}
      />
    );
  }


  render() {
    const { squares, width, height } = this.props;
    return (
      <section className="board">
        {
          squares.map((row, y) => (
            (
              // eslint-disable-next-line react/no-array-index-key
              <div key={y} className="board-row">
                {row.map((col, x) => this.renderSquare(x, y))}
              </div>

            )
          ))
        }
      </section>
    );
  }
}

Board.propTypes = {
  width: PropTypes.number.isRequired,
  height: PropTypes.number.isRequired,
  latestX: PropTypes.number.isRequired,
  latestY: PropTypes.number.isRequired,
  squares: PropTypes.arrayOf(PropTypes.arrayOf(PropTypes.number)).isRequired,
  onClick: PropTypes.func.isRequired,
};

export default Board;
