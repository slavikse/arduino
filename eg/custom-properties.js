const five = require('johnny-five');
const board = new five.Board();

board.on('ready', () => {
  const sensor = new five.Sensor({
    pin: 'A0',
    custom: {
      a: 1,
      b: 2,
    },
  });

  console.log(sensor.custom.a);
  console.log(sensor.custom.b);
});
