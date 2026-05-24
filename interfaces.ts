
export interface Task{
  Id:string;
  type : string;
  description : string;
  assignedTo ?: string;
}

export interface Column{
  id : string;
  name : string;
  taskids : string[]; 
}

export interface Board{
  id : string;
  name : string;

  columns : Record<string, Column>;
  tasks : Record<string , Task>;
}

export type auditChanges = 'TASK_CREATED' | 'TASK_MOVED' | 'TASK_DONE';

export interface AuditLog{
  id : string;
  TaskId: string;
  action : auditChanges;
  timestamp : Date;
  userId : string;

  metaData ?: {
    fromColId ?: string;
    toColId ?: string;
  };
}