Js.log("Hello, BuckleScript and Reason!!");

let main = () => {
  Js.log("Running Main Tests");
  OfDemo.test() |> ignore;
  OfDemo.testAsObservable() |> ignore;
  RxJsFromArrayDemo.test() |> ignore;
  RxJsZipDemoSameTypes.test() |> ignore;
  FromArrayDemo.test();
};
main();