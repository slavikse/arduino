const five = require('johnny-five');
const board = new five.Board();

board.on('ready', () => {
  const led = new five.Led(7);
  led.on();

  board.on('exit', () => {
    led.off();
  });
});
