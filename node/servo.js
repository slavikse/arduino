const five = require('johnny-five');
const board = new five.Board();

board.on('ready', () => {
  var servo = new five.Servo({
    pin: 7,
    type: 'continuous',
  });
  servo.ccw();
});
