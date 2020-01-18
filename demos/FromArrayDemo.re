// open RxJsTypes;
// module Observable = {
//   type t('a) = observable('a);

//   type subscribeParams('a) = {
//     next: option('a => unit),
//     error: option(Js.Json.t => unit),
//     complete: option(unit => unit),
//   };

//   [@bs.send]
//   external subscribe_: (t('a), subscribeParams('a)) => subscription =
//     "subscribe";

//   let subscribe =
//       (
//         self: t('a),
//         ~next: option('a => unit)=?,
//         ~error: option(Js.Json.t => unit)=?,
//         ~complete: option(unit => unit)=?,
//         (),
//       ) => {
//     let args = {next, error, complete};
//     subscribe_(self, args);
//   };

//   [@bs.send]
//   external subscribe0: (t('a), observer('a)) => subscription = "subscribe";

//   [@bs.module "rxjs/_esm2015"] [@bs.scope "Observable"]
//   external make: (observer('a) => option(unit => unit)) => observable('a) =
//     "create";
// };
/* import { from } from 'rxjs';

   const array = [10, 20, 30];
   const result = from(array);

   result.subscribe(x => console.log(x));

   // Logs:
   // 10
   // 20
   // 30 */

// [@bs.module "rxjs/_esm2015"]
// external fromArray: array('a) => Rx.Observable.t('a) = "from";
let array = [|10, 20, 30|];

let result:Rx.Observable.t('a) = Rx.Observable.fromArray(array);
let test = () =>
  result->Rx.Observable.subscribe(
    ~next=x => Js.log2("FromArrayDemo: Click value ", x),
    ~error=err => Js.log2("FromArrayDemo: something wrong occurred", err),
    ~complete=() => Js.log("FromArrayDemo: done"),
    ~closed=true,
  );