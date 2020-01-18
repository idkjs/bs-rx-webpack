Js.log("Hello, BuckleScript and Reason!!");

let main = () => {
  Js.log("Running Main Tests");
  OfDemo.test()|>ignore;
  OfDemo.testAsObservable()|>ignore;
  FromArrayDemo.test();
};
main();