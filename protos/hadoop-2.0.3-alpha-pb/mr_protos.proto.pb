

mr_protos.protoyarn_protos.proto"=

JobIdProto#
app_id (2.ApplicationIdProto

id ("Y
TaskIdProto
job_id (2.JobIdProto!
	task_type (2.TaskTypeProto

id ("?
TaskAttemptIdProto
task_id (2.TaskIdProto

id ("A
CounterProto
name (	
display_name (	
value ("a
CounterGroupProto
name (	
display_name (	(
counters (2.StringCounterMapProto"D
CountersProto3
counter_groups (2.StringCounterGroupMapProto"ß
TaskReportProto
task_id (2.TaskIdProto#

task_state (2.TaskStateProto
progress (

start_time (
finish_time ( 
counters (2.CountersProto-
running_attempts (2.TaskAttemptIdProto/
successful_attempt (2.TaskAttemptIdProto
diagnostics	 (	"ÿ
TaskAttemptReportProto,
task_attempt_id (2.TaskAttemptIdProto2
task_attempt_state (2.TaskAttemptStateProto
progress (

start_time (
finish_time ( 
counters (2.CountersProto
diagnostic_info (	
state_string (	
phase	 (2.PhaseProto
shuffle_finish_time
 (
sort_finish_time (
node_manager_host (	
node_manager_port (
node_manager_http_port ('
container_id (2.ContainerIdProto"Å
JobReportProto
job_id (2.JobIdProto!
	job_state (2.JobStateProto
map_progress (
reduce_progress (
cleanup_progress (
setup_progress (

start_time (
finish_time (
user	 (	
jobName
 (	
trackingUrl (	
diagnostics (	
jobFile (	
am_infos (2.AMInfoProto
submit_time (
is_uber (:false"‹
AMInfoProto:
application_attempt_id (2.ApplicationAttemptIdProto

start_time ('
container_id (2.ContainerIdProto
node_manager_host (	
node_manager_port (
node_manager_http_port ("—
TaskAttemptCompletionEventProto'

attempt_id (2.TaskAttemptIdProto6
status (2&.TaskAttemptCompletionEventStatusProto!
map_output_server_address (	
attempt_run_time (
event_id ("B
StringCounterMapProto
key (	
value (2.CounterProto"L
StringCounterGroupMapProto
key (	!
value (2.CounterGroupProto*$
TaskTypeProto
MAP

REDUCE*n
TaskStateProto

TS_NEW
TS_SCHEDULED

TS_RUNNING
TS_SUCCEEDED
	TS_FAILED
	TS_KILLED*_

PhaseProto

P_STARTING	
P_MAP
	P_SHUFFLE

P_SORT
P_REDUCE
	P_CLEANUP*ã
TaskAttemptStateProto

TA_NEW
TA_STARTING

TA_RUNNING
TA_COMMIT_PENDING
TA_SUCCEEDED
	TA_FAILED
	TA_KILLED*q
JobStateProto	
J_NEW
J_INITED
	J_RUNNING
J_SUCCEEDED
J_FAILED
J_KILLED
J_ERROR*Ñ
%TaskAttemptCompletionEventStatusProto
TACE_FAILED
TACE_KILLED
TACE_SUCCEEDED
TACE_OBSOLETE
TACE_TIPFAILEDB6
$org.apache.hadoop.mapreduce.v2.protoBMRProtosà†