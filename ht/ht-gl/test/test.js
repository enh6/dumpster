let Test1 = require('./tetrahedron.js');
let Test2 = require('./texture.js')

const width = 500, height = 500;

let tests = [
  {finished: true},
  new Test1(width, height),
  new Test2(width, height)
];

let i = 0;

let runTests = function() {
  if (tests[i].finished) {
    i++;
    if (i === tests.length) {
      return;
    }
    tests[i].init();
    tests[i].draw();
    tests[i].destroy(3000);
  }
  setTimeout(runTests, 2000);
}

runTests();

