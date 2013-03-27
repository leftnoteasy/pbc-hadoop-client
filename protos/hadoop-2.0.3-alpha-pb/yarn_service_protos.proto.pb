
ô
yarn_service_protos.protoSecurity.protoyarn_protos.proto"™
%RegisterApplicationMasterRequestProto:
application_attempt_id (2.ApplicationAttemptIdProto
host (	
rpc_port (
tracking_url (	"±
&RegisterApplicationMasterResponseProto)
minimumCapability (2.ResourceProto)
maximumCapability (2.ResourceProto1
application_ACLs (2.ApplicationACLMapProto"Ì
#FinishApplicationMasterRequestProto:
application_attempt_id (2.ApplicationAttemptIdProto
diagnostics (	
tracking_url (	>
final_application_status (2.FinalApplicationStatusProto"&
$FinishApplicationMasterResponseProto"Á
AllocateRequestProto:
application_attempt_id (2.ApplicationAttemptIdProto"
ask (2.ResourceRequestProto"
release (2.ContainerIdProto
response_id (
progress ("Y
AllocateResponseProto%
AM_response (2.AMResponseProto
num_cluster_nodes ("
GetNewApplicationRequestProto"£
GetNewApplicationResponseProto+
application_id (2.ApplicationIdProto)
minimumCapability (2.ResourceProto)
maximumCapability (2.ResourceProto"O
 GetApplicationReportRequestProto+
application_id (2.ApplicationIdProto"X
!GetApplicationReportResponseProto3
application_report (2.ApplicationReportProto"k
SubmitApplicationRequestProtoJ
application_submission_context (2".ApplicationSubmissionContextProto" 
SubmitApplicationResponseProto"J
KillApplicationRequestProto+
application_id (2.ApplicationIdProto"
KillApplicationResponseProto"
GetClusterMetricsRequestProto"S
GetClusterMetricsResponseProto1
cluster_metrics (2.YarnClusterMetricsProto" 
GetAllApplicationsRequestProto"P
GetAllApplicationsResponseProto-
applications (2.ApplicationReportProto"
GetClusterNodesRequestProto"E
GetClusterNodesResponseProto%
nodeReports (2.NodeReportProto"y
GetQueueInfoRequestProto
	queueName (	
includeApplications (
includeChildQueues (
	recursive ("?
GetQueueInfoResponseProto"
	queueInfo (2.QueueInfoProto""
 GetQueueUserAclsInfoRequestProto"R
!GetQueueUserAclsInfoResponseProto-
queueUserAcls (2.QueueUserACLInfoProto"\
StartContainerRequestProto>
container_launch_context (2.ContainerLaunchContextProto"M
StartContainerResponseProto.
service_response (2.StringBytesMapProto"D
StopContainerRequestProto'
container_id (2.ContainerIdProto"
StopContainerResponseProto"I
GetContainerStatusRequestProto'
container_id (2.ContainerIdProto"H
GetContainerStatusResponseProto%
status (2.ContainerStatusProtoB7
org.apache.hadoop.yarn.protoBYarnServiceProtosˆ 