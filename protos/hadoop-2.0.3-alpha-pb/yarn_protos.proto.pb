
�-
yarn_protos.protoSecurity.proto"x
YarnRemoteExceptionProto
message (	
trace (	

class_name (	(
cause (2.YarnRemoteExceptionProto";
ApplicationIdProto

id (
cluster_timestamp ("[
ApplicationAttemptIdProto+
application_id (2.ApplicationIdProto
	attemptId ("w
ContainerIdProto#
app_id (2.ApplicationIdProto2
app_attempt_id (2.ApplicationAttemptIdProto

id ("6
ResourceProto
memory (
virtual_cores ("!
PriorityProto
priority ("�
ContainerProto
id (2.ContainerIdProto
nodeId (2.NodeIdProto
node_http_address (	 
resource (2.ResourceProto 
priority (2.PriorityProto#
state (2.ContainerStateProto2
container_token (2.hadoop.common.TokenProto/
container_status (2.ContainerStatusProto"{
ApplicationStatusProto
response_id (:
application_attempt_id (2.ApplicationAttemptIdProto
progress ("�
ApplicationMasterProto+
application_id (2.ApplicationIdProto
host (	
rpc_port (
trackingUrl (	'
status (2.ApplicationStatusProto)
state (2.YarnApplicationStateProto/
client_token (2.hadoop.common.TokenProto
containerCount (
amFailCount	 (
diagnostics
 (	: "D
URLProto
scheme (	
host (	
port (
file (	"�
LocalResourceProto
resource (2	.URLProto
size (
	timestamp (%
type (2.LocalResourceTypeProto1

visibility (2.LocalResourceVisibilityProto
pattern (	"�
#ApplicationResourceUsageReportProto
num_used_containers (
num_reserved_containers (&
used_resources (2.ResourceProto*
reserved_resources (2.ResourceProto(
needed_resources (2.ResourceProto"�
ApplicationReportProto*
applicationId (2.ApplicationIdProto
user (	
queue (	
name (	
host (	
rpc_port (/
client_token (2.hadoop.common.TokenProto'
status (2.ApplicationStatusProto:
yarn_application_state	 (2.YarnApplicationStateProto(
masterContainer
 (2.ContainerProto
trackingUrl (	
diagnostics (	:N/A
	startTime (

finishTime (>
final_application_status (2.FinalApplicationStatusProto@
app_resource_Usage (2$.ApplicationResourceUsageReportProto
originalTrackingUrl (	?
currentApplicationAttemptId (2.ApplicationAttemptIdProto")
NodeIdProto
host (	
port ("h
NodeHealthStatusProto
is_node_healthy (
health_report (	
last_health_report_time ("�
NodeReportProto
nodeId (2.NodeIdProto
httpAddress (	
rackName (	
used (2.ResourceProto"

capability (2.ResourceProto
numContainers (2
node_health_status (2.NodeHealthStatusProto#

node_state	 (2.NodeStateProto"�
ResourceRequestProto 
priority (2.PriorityProto
	host_name (	"

capability (2.ResourceProto
num_containers ("�
AMResponseProto
reboot (
response_id (-
allocated_containers (2.ContainerProto;
completed_container_statuses (2.ContainerStatusProto
limit (2.ResourceProto'
updated_nodes (2.NodeReportProto"�
!ApplicationSubmissionContextProto+
application_id (2.ApplicationIdProto
application_name (	:N/A
user (	
queue (	:default 
priority (2.PriorityProto7
am_container_spec (2.ContainerLaunchContextProto)
cancel_tokens_when_complete (:true
unmanaged_am (:false"Y
ApplicationACLMapProto/

accessType (2.ApplicationAccessTypeProto
acl (	: "4
YarnClusterMetricsProto
num_node_managers ("�
QueueInfoProto
	queueName (	
capacity (
maximumCapacity (
currentCapacity (
state (2.QueueStateProto$
childQueues (2.QueueInfoProto-
applications (2.ApplicationReportProto"L
QueueUserACLInfoProto
	queueName (	 
userAcls (2.QueueACLProto"�
ContainerLaunchContextProto'
container_id (2.ContainerIdProto
user (	 
resource (2.ResourceProto4
localResources (2.StringLocalResourceMapProto
container_tokens (*
service_data (2.StringBytesMapProto*
environment (2.StringStringMapProto
command (	1
application_ACLs	 (2.ApplicationACLMapProto"�
ContainerStatusProto'
container_id (2.ContainerIdProto#
state (2.ContainerStateProto
diagnostics (	:N/A
exit_status (:-1000":
StringURLMapProto
key (	
value (2	.URLProto"N
StringLocalResourceMapProto
key (	"
value (2.LocalResourceProto"2
StringStringMapProto
key (	
value (	"1
StringBytesMapProto
key (	
value ("|
ApplicationStateDataProto
submit_time (J
application_submission_context (2".ApplicationSubmissionContextProto"|
 ApplicationAttemptStateDataProto-
	attemptId (2.ApplicationAttemptIdProto)
master_container (2.ContainerProto*?
ContainerStateProto	
C_NEW
	C_RUNNING

C_COMPLETE*t
YarnApplicationStateProto
NEW
	SUBMITTED
RUNNING
FINISHED

FAILED

KILLED
ACCEPTED*c
FinalApplicationStatusProto
APP_UNDEFINED 
APP_SUCCEEDED

APP_FAILED

APP_KILLED*H
LocalResourceVisibilityProto

PUBLIC
PRIVATE
APPLICATION*<
LocalResourceTypeProto
ARCHIVE
FILE
PATTERN*s
NodeStateProto

NS_NEW

NS_RUNNING
NS_UNHEALTHY
NS_DECOMMISSIONED
NS_LOST
NS_REBOOTED*N
ApplicationAccessTypeProto
APPACCESS_VIEW_APP
APPACCESS_MODIFY_APP*/
QueueStateProto
	Q_STOPPED
	Q_RUNNING*H
QueueACLProto
QACL_SUBMIT_APPLICATIONS
QACL_ADMINISTER_QUEUEB0
org.apache.hadoop.yarn.protoB
YarnProtos��