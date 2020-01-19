/* they're not the same at the Reason type system level. the equivalency is only for compiled output. and it's not clear to me that the compile output of records has been made a 'shared' i.e. public representation like for e.g. arrays, tuples
   i wouldn't change Example for BS7
   module Unsubscribable = {
     type t('a) = {mutable unsubscribe: unit => unit};
   };
   module Unsubscribable = {
     type t('a) = Js.t({.. unsubscribe: unit => unit} as 'a);
   };
   module Unsubscribable = {
     type t('a) = {mutable unsubscribe: unit => unit};
   }; */
module Unsubscribable = {
  type t('a) = Js.t({.. unsubscribe: unit => unit} as 'a);
};

module Observer = {
  type t('a, 'e) = {
    closed: bool,
    next: 'a => unit,
    error: 'e => unit,
    complete: unit => unit,
  };
};
module Observer2 = {
  type t('a,'e);

  [@bs.send] external closed: unit => unit = "closed";
  [@bs.send] external next: (t('a,'e), 'a) => unit = "next";
  [@bs.send] external error: (t('a,'e), 'e) => unit = "error";
  [@bs.send] external complete: unit => unit = "complete";
};
type observer('a);
type observable('a);
type connectableObservable('a);
type unaryFunction('a, 'b) = 'a => 'b;
type operatorFunction('a, 'b) =
  unaryFunction(observable('a), observable('b));
type subscription;
type subject('a);
type asyncSubject('a);
type behaviorSubject('a);
type replaySubject('a);
type websocketSubject('a);

type scheduler;