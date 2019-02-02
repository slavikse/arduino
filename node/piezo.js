const five = require('johnny-five');
const board = new five.Board();

board.on('ready', () => {
  const piezo = new five.Piezo(7);

  board.repl.inject({
    play() {
      piezo.play({
        song: [
          ['C4', 1 / 4],
          ['D4', 1 / 4],
          ['F4', 1 / 4],
          ['D4', 1 / 4],
          ['A4', 1 / 4],
          [null, 1 / 4],
          ['A4', 1],
          ['G4', 1],
          [null, 1 / 2],
          ['C4', 1 / 4],
          ['D4', 1 / 4],
          ['F4', 1 / 4],
          ['D4', 1 / 4],
          ['G4', 1 / 4],
          [null, 1 / 4],
          ['G4', 1],
          ['F4', 1],
          [null, 1 / 2],
        ],
        tempo: 100,
      });
    },
  });
});
