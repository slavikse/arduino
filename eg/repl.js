const five = require('johnny-five');
const board = new five.Board();

board.on('ready', () => {
  console.log('Ready event. Repl instance auto-initialized!');

  const led = new five.Led(13);

  board.repl.inject({
    on() {
      led.on();
    },
    off() {
      led.off();
    },
  });
});
