'use strict';

const http = require('http');
const { parse } = require('querystring');

const html = `
<!doctype html>
<html>
<head>
<style>* {
font-size: 2rem;
}</style>
</head>
<body>
<h1>Голосовое управление со смартфона по Интернет:</h1>
<ul>
  <h3>достань</h3>
</ul>

<h1>Результат распознавания голоса:</h1>
<h3 id="result"></h3>

<script>
const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
const SpeechGrammarList = window.SpeechGrammarList || window.webkitSpeechGrammarList;
// const SpeechRecognitionEvent = window.SpeechRecognitionEvent ||
// window.webkitSpeechRecognitionEvent;

const words = [
  'Достань',
];

const grammar = '#JSGF V1.0; grammar words; public <words> = ' + words.join(' | ') + ' ;';
const speechRecognitionList = new SpeechGrammarList();
const recognition = new SpeechRecognition();
speechRecognitionList.addFromString(grammar, 1);

recognition.grammars = speechRecognitionList;
recognition.continuous = true;
recognition.lang = 'ru-RU';
recognition.maxAlternatives = 1;
recognition.start();

const synth = window.speechSynthesis;
// const voices = synth.getVoices();

const utter = new SpeechSynthesisUtterance();

function send(command) {
  const http = new XMLHttpRequest();
  const url = '/';
  // 'command=on';
  const params = command;
  
  http.open('POST', url, true);
  http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  
  http.onreadystatechange = () => {
    if(http.readyState === 4 && http.status === 200) {
      console.log(http.responseText);
    }
  }

  http.send(params);
}

recognition.onresult = ({ results }) => {
  const last = results.length - 1;
  const text = results[last][0].transcript;

  console.log(results[0][0].confidence);
  const message = text.trim();

  utter.lang = 'ru-RU';
  // utter.pitch = 0.7;
  // utter.rate = 0.9;
  // utter.voice = voices[0];
  utter.text = message;

  switch (message) {
    case 'пасхалка':
      utter.text = 'Не надо тут выпрашивать, что ещё не реализовано я СКАЗАЛ!!! А-ТА-ТА!!!';
      break;

    case 'Достань':
      utter.text = 'Достаю!';
      send('command=Достань');
      break;

    default:
  }
  
  synth.speak(utter);
  console.log(utter.text);
  
  result.innerHTML = utter.text;
};

recognition.onspeechend = () => {
  console.log('onspeechend');

  setTimeout(() => {
    recognition.start();
  }, 2000);
};
</script>
</body>
</html>
`;

const five = require('johnny-five');
const board = new five.Board();

let motor;
let servo;
let led;

board.on('ready', () => {
  motor = new five.Motor(5);
  servo = new five.Servo(7);

  servo.to(0);

  board.on('exit', () => {
    motor.stop();
    servo.stop();
  });
});

const server = http.createServer((req, res) => {
  if (req.method === 'POST') {
    let body = '';

    req.on('data', chunk => {
      body += chunk.toString();
    });

    req.on('end', () => {
      const b = parse(body);
      console.log(b.command);

      switch (b.command) {
        case 'Достань':
          board.wait(1000, () => {
            servo.to(100, 5000);
          });

          board.wait(7000, () => {
            motor.forward(80);
            // motor.revers(80);
          });
          break;

        default:
      }
    });
  }

  res.end(html);
});

server.listen(8080);
