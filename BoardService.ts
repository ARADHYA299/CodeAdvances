import { AuditLog, Board } from "./interfaces";

export class BoardService{
  private board : Board;
  private logs : AuditLog[] = [];


  public constructor(board : Board){
    this.board = board;
  }

  public moveTask(taskId : string , fromColId : string, toColId : string): boolean{
    const fromCol = this.board.columns[fromColId];
    const toCol = this.board.columns[toColId];

    if (!fromCol || !toCol) {
      return false;
    }

    fromCol.taskids = fromCol.taskids.filter(id => id !== taskId);
    toCol.taskids.push(taskId);

    const newLog : AuditLog = {
      id : `log - ${Date.now()}`,
      TaskId : taskId,
      action : 'TASK_MOVED',
      timestamp : new Date(),
      userId : 'user1',
      metaData : {
        fromColId,
        toColId
      }
    };

    this.logs.push(newLog);

    return true;
  }
}