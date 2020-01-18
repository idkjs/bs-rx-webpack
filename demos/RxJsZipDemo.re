/*
 see: https://rxjs.dev/api/index/function/zip
 import { zip, of } from 'rxjs';
 import { map } from 'rxjs/operators';

 let age$ = of<number>(27, 25, 29);
 let name$ = of<string>('Foo', 'Bar', 'Beer');
 let isDev$ = of<boolean>(true, true, false);

 zip(age$, name$, isDev$).pipe(
   map(([age, name, isDev]) => ({ age, name, isDev })),
 )
 .subscribe(x => console.log(x));

 // outputs
 // { age: 27, name: 'Foo', isDev: true }
 // { age: 25, name: 'Bar', isDev: true }
 // { age: 29, name: 'Beer', isDev: false }
     */
open RxJsTypes;
module Operator = {
  [@bs.module "rxjs/operators"]
  external map: ([@bs.uncurry] ('a => 'b)) => unaryFunction('a, 'b) = "map";

  /* call pipe on one argument */
  [@bs.module "rxjs/operators"]
  external pipe: ('a, unaryFunction('a, 'b)) => 'b = "pipe";

  /* call pipe on multiples arguments. Consider using variadic? */
  [@bs.module "rxjs/operators"]
  external pipe3:
    (
      'a,
      unaryFunction('a, 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd)
    ) =>
    'd =
    "pipe";
};
module Observable = {
  type t('a) = observable('a);

  type subscribeParams('a) = {
    next: option('a => unit),
    error: option(Js.Json.t => unit),
    complete: option(unit => unit),
  };

  [@bs.send]
  external subscribe_: (t('a), subscribeParams('a)) => subscription =
    "subscribe";

  let subscribe =
      (
        self: t('a),
        ~next: option('a => unit)=?,
        ~error: option(Js.Json.t => unit)=?,
        ~complete: option(unit => unit)=?,
        (),
      ) => {
    let args = {next, error, complete};
    subscribe_(self, args);
  };

  [@bs.send]
  external subscribe0: (t('a), observer('a)) => subscription = "subscribe";

  [@bs.module "rxjs/_esm2015"] [@bs.scope "Observable"]
  external make: (observer('a) => option(unit => unit)) => observable('a) =
    "create";

  [@bs.module "rxjs/_esm2015"] [@bs.variadic]
  external of_: array('a) => observer('a) = "of";
  [@bs.module "rxjs/_esm2015"]
  external fromArray: array('a) => observable('a) = "from";

  [@bs.module "rxjs/_esm2015"]
  external zip: array('a) => observable('a) = "zip";
};

type zipArray;
external castTo: 'a => zipArray = "%identity";
external castToA: 'a => 'a = "%identity";
let age = Observable.of_([|27, 25, 29|])->castTo;
let name = Observable.of_([|"Foo", "Bar", "Beer"|])->castTo;
let isDev = Observable.of_([|true, true, false|])->castTo;
let array = [|age, isDev, name|]->castToA;
// let arrayObs = Observable.fromArray([|age, isDev, name|]);
let arrayObs = Observable.fromArray(array);
// let zippedObs = Observable.zip(arrayObs);
let arrayToA = array |> castToA;
let zipped = Observable.zip(arrayToA);
/* let o1 = fromArray([|1, 2, 3, 4|]);
   o1
   ->pipe3(
       map(i => i + 20),
       filteri((x, i) => {
         expectToEqual(i->Js.typeof, "number");
         x mod 2 == 0;
       }),
       toArray(),
     )
   ->subscribe(~next=arr => expectToEqual(arr, [|22, 24|]), ()); */
// let operator = zipped -> Operator.(pipe3(map(i => Js.log(i))));
// let test = () =>
  // zipped->Observable.subscribe(
  //   ~next=x => Js.log2("RxJsZipDemo: value ", x),
  //   ~error=err => Js.log2("RxJsZipDemo: something wrong occurred", err),
  //   ~complete=() => Js.log("RxJsZipDemo: done"),
  //   (),
  // );