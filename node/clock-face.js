const five = require('johnny-five');
const board = new five.Board();

const pinsLeds = [
  { pin: 13, ledId: 1 },
  { pin: 12, ledId: 2 },
  { pin: 11, ledId: 4 },
  { pin: 10, ledId: 6 },
  { pin: 9, ledId: 7 },
  { pin: 8, ledId: 9 },
  { pin: 7, ledId: 10 },
];

const leds = {};

// Соответствие цифры с используемыми leds[].
const digits = {
  0: [2, 4, 6, 7, 9, 1],
  1: [4, 6],
  2: [1, 2, 6, 7, 10],
  3: [2, 4, 6, 7, 10],
  4: [4, 6, 9, 10],
  5: [2, 4, 7, 9, 10],
  6: [1, 2, 4, 7, 9, 10],
  7: [4, 6, 7],
  8: [1, 2, 4, 6, 7, 9, 10],
  9: [4, 6, 7, 9, 10],
};

// Для диапозона от 0 до 9.
const maximumDigit = 10;
let currentDigit = -1;

board.on('ready', () => {
  pinsLeds.forEach(({ pin, ledId }) => {
    leds[ledId] = new five.Led(pin);
  });

  setInterval(() => {
    turn('off');

    currentDigit = (currentDigit + 1) % maximumDigit;

    turn('on');
  }, 1000);

  board.on('exit', () => {
    Object.values(leds).forEach(led => led.off());
  });
});

function turn(type) {
  if (digits[currentDigit]) {
    digits[currentDigit].forEach((ledId) => {
      leds[ledId][type]();
    });
  }
}
