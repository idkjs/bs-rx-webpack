open Jest;
open Rx.Testing;
open TestScheduler;
open TestUtils;

/*
 let o1 = fromArray([|1, 2, 3, 4, 5, 6|]);
 o1
 ->pipe1(toArray())
 ->subscribe(
     ~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 5, 6|]),
     ~complete=() => Js.log("o1 complete"),
     (),
   );
   */
/** @test {fromArray} */
describe("fromArray operator", () => {
  testMarbles(
    "fromArray([10, 20, 30]): should create an observable from an array", ts
    => {
      // let e1 = ts |> hot("---a--b-");
      let e1 =
        ts
        |> cold(
              Rx.Observable.fromArray([|10, 20, 30|])
             |> Rx.pipe1(
                  // for the purpose of making a nice diagram, spread out the synchronous emissions
                  Rx.Operators.concatMap((x, i) =>
                    Rx.of_(x)
                    |> Rx.pipe1(Rx.Operators.delay(0 == 0 ? 0 : 20, ~scheduler=ts |> TestScheduler.asScheduler, ()))
                  ),
                ),
           )
        |> ColdObservable.asObservable;
      let expected = "x-y-(z|)";
      // let values = {"w": [|"a", "b"|]};
      let values = {x: 10, y: 20, z: 30};
      let result =
        e1
        |> HotObservable.asObservable
        |> Rx_Observable2.(Rx.pipe1(Rx.Operators.fromArray()));
      let result =
        e1
        |> HotObservable.asObservable
        |> Rx_Observable.(fromArray(array) |> Rx.Observable.asObservable);
      let result =
        e1 |> HotObservable.asObservable |> Rx.pipe1(Rx.Operators.toArray());
      ts |> expectObservable(result) |> toBeObservable(expected, values);
      ts
      |> expectSubscriptions(e1 |> HotObservable.subscriptions)
      |> toBeSubscriptions(subs);
      // expectObservable(e1.pipe(toArray())).toBe(expected, { w: ["a", "b"] });
      // expectSubscriptions(e1.subscriptions).toBe(e1subs);
    })
    // it("should be never when source is never", () => {
    //   let e1 =  cold("-");
    //   let e1subs =   "^";
    //   let expected = "-";
    //   expectObservable(e1.pipe(toArray())).toBe(expected);
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should be never when source is empty", () => {
    //   let e1 =  cold("|");
    //   let e1subs =   "(^!)";
    //   let expected = "(w|)";
    //   expectObservable(e1.pipe(toArray())).toBe(expected, { w: [] });
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should be never when source doesn\"t complete", () => {
    //   let e1 = hot("--x--^--y--");
    //   let e1subs =      "^     ";
    //   let expected =    "------";
    //   expectObservable(e1.pipe(toArray())).toBe(expected);
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should reduce observable without values into an array of length zero", () => {
    //   let e1 = hot("-x-^---|");
    //   let e1subs =    "^   !";
    //   let expected =  "----(w|)";
    //   expectObservable(e1.pipe(toArray())).toBe(expected, { w: [] });
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should reduce the a single value of an observable into an array", () => {
    //   let e1 = hot("-x-^--y--|");
    //   let e1subs =    "^     !";
    //   let expected =  "------(w|)";
    //   expectObservable(e1.pipe(toArray())).toBe(expected, { w: ["y"] });
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should allow multiple subscriptions", () => {
    //   let e1 = hot("-x-^--y--|");
    //   let e1subs =    "^     !";
    //   let expected =  "------(w|)";
    //   let result = e1.pipe(toArray());
    //   expectObservable(result).toBe(expected, { w: ["y"] });
    //   expectObservable(result).toBe(expected, { w: ["y"] });
    //   expectSubscriptions(e1.subscriptions).toBe([e1subs, e1subs]);
    // });
    // it("should allow unsubscribing explicitly and early", () => {
    //   let e1 =   hot("--a--b----c-----d----e---|");
    //   let unsub =    "        !                 ";
    //   let e1subs =   "^       !                 ";
    //   let expected = "---------                 ";
    //   expectObservable(e1.pipe(toArray()), unsub).toBe(expected);
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should not break unsubscription chains when result is unsubscribed explicitly", () => {
    //   let e1 =   hot("--a--b----c-----d----e---|");
    //   let e1subs =   "^       !                 ";
    //   let expected = "---------                 ";
    //   let unsub =    "        !                 ";
    //   let result = e1.pipe(
    //     mergeMap((x: string) => of(x)),
    //     toArray(),
    //     mergeMap((x: Array<string>) => of(x))
    //   );
    //   expectObservable(result, unsub).toBe(expected);
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should work with error", () => {
    //   let e1 = hot("-x-^--y--z--#", { x: 1, y: 2, z: 3 }, "too bad");
    //   let e1subs =    "^        !";
    //   let expected =  "---------#";
    //   expectObservable(e1.pipe(toArray())).toBe(expected, null, "too bad");
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // it("should work with throw", () => {
    //   let e1 =  cold("#");
    //   let e1subs =   "(^!)";
    //   let expected = "#";
    //   expectObservable(e1.pipe(toArray())).toBe(expected);
    //   expectSubscriptions(e1.subscriptions).toBe(e1subs);
    // });
    // type("should infer the element type", () => {
    //   let typeValue = {
    //     val: 3
    //   };
    //   of(typeValue).pipe(toArray()).subscribe(x => { x[0].val.toString(); });
    // });
});