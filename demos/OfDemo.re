/* import { of } from 'rxjs';

   of(10, 20, 30)
   .subscribe(
     next => console.log('next:', next),
     err => console.log('error:', err),
     () => console.log('the end'),
   );
   // result:
   // 'next: 10'
   // 'next: 20'
   // 'next: 30' */
let array = [|10, 20, 30|];

let result = Rx_Observable.of_(array);
let observable = result->Rx.Observable.asObservable;
let test = () =>
  result->Rx.Observable.subscribe(
    ~next=x => Js.log2("OfDemo:", x),
    ~error=err => Js.log2("OfDemo: something wrong occurred", err),
    ~complete=() => Js.log("OfDemo: done"),
    ~closed=true,
  );
let testAsObservable = () =>
  observable->Rx.Observable.subscribe(
    ~next=x => Js.log2("OfDemo_AsObservable:", x),
    ~error=
      err => Js.log2("OfDemo_AsObservable: something wrong occurred", err),
    ~complete=() => Js.log("OfDemo_AsObservable: done"),
    ~closed=true,
  );