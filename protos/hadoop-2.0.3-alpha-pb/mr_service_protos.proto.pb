
¨
mr_service_protos.protoSecurity.protomr_protos.protoyarn_protos.proto"7
GetJobReportRequestProto
job_id (2.JobIdProto"@
GetJobReportResponseProto#

job_report (2.JobReportProto":
GetTaskReportRequestProto
task_id (2.TaskIdProto"C
GetTaskReportResponseProto%
task_report (2.TaskReportProto"P
 GetTaskAttemptReportRequestProto,
task_attempt_id (2.TaskAttemptIdProto"Y
!GetTaskAttemptReportResponseProto4
task_attempt_report (2.TaskAttemptReportProto"6
GetCountersRequestProto
job_id (2.JobIdProto"<
GetCountersResponseProto 
counters (2.CountersProto"t
*GetTaskAttemptCompletionEventsRequestProto
job_id (2.JobIdProto
from_event_id (

max_events ("j
+GetTaskAttemptCompletionEventsResponseProto;
completion_events (2 .TaskAttemptCompletionEventProto"\
GetTaskReportsRequestProto
job_id (2.JobIdProto!
	task_type (2.TaskTypeProto"E
GetTaskReportsResponseProto&
task_reports (2.TaskReportProto"J
GetDiagnosticsRequestProto,
task_attempt_id (2.TaskAttemptIdProto"2
GetDiagnosticsResponseProto
diagnostics (	"2
KillJobRequestProto
job_id (2.JobIdProto"
KillJobResponseProto"5
KillTaskRequestProto
task_id (2.TaskIdProto"
KillTaskResponseProto"K
KillTaskAttemptRequestProto,
task_attempt_id (2.TaskAttemptIdProto"
KillTaskAttemptResponseProto"K
FailTaskAttemptRequestProto,
task_attempt_id (2.TaskAttemptIdProto"
FailTaskAttemptResponseProtoB=
$org.apache.hadoop.mapreduce.v2.protoBMRServiceProtosˆ 