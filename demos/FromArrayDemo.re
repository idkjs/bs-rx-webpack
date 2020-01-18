/**
https://rxjs.dev/api/index/function/from

```js
import { from } from 'rxjs';

const array = [10, 20, 30];
const result = from(array);

result.subscribe(x => console.log(x));

// Logs:
// 10
// 20
// 30
```
 */
let array = [|10, 20, 30|];

let result = Rx_Observable.(fromArray(array) |> Rx.Observable.asObservable);
// let observable = result -> Rx.Observable.asObservable;
let test = () =>
  result->Rx.Observable.subscribe(
    ~next=x => Js.log2("FromArrayDemo: Click value ", x),
    ~error=err => Js.log2("FromArrayDemo: something wrong occurred", err),
    ~complete=() => Js.log("FromArrayDemo: done"),
    ~closed=true,
  );