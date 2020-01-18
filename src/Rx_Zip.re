open Rx_Observable.Observable;

type operator('a, 'b) = t('a) => t('b);

/*
 [internal/zipAll.js](https://github.com/ReactiveX/rxjs/blob/master/src/internal/operators/zipAll.ts)

 export function zipAll<T>(): OperatorFunction<ObservableInput<T>, T[]>;
 export function zipAll<T>(): OperatorFunction<any, T[]>;
 export function zipAll<T, R>(project: (...values: T[]) => R): OperatorFunction<ObservableInput<T>, R>;
 export function zipAll<R>(project: (...values: Array<any>) => R): OperatorFunction<any, R>;

 export function zipAll<T, R>(project?: (...values: Array<any>) => R): OperatorFunction<T, R> {
   return (source: Observable<T>) => source.lift(new ZipOperator(project));
 } */

[@bs.module "rxjs/operators"]
external zip: ([@bs.uncurry] (('err, t('a)) => t('b))) => operator('a, 'b) =
  "zip";
// [@bs.module "rxjs/operators"]
// external zip: (t('e, 'a), t('e, 'a)) => t('e, array('a)) = "zip";
[@bs.module "rxjs/operators"]
external zipAll:
  ([@bs.uncurry] (('err, t('a)) => t('b))) => operator('a, array('b)) =
  "zipAll" /*   "zipAll0"*/;
// [@bs.module "rxjs/operators"]
// external zipAll: (t('e, 'a), array(t('e, 'a))) => t('e, array('a)) =
//   "zipAll";
// [@bs.module "rxjs/operators"]
// external zipAll0:
//   ([@bs.uncurry] array(('err, t('a)) => t('b))) => operator('a, 'b) =