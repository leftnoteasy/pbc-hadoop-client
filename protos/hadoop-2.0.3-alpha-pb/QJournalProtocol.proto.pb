
È
QJournalProtocol.protohadoop.hdfs
hdfs.proto"$
JournalIdProto

identifier (	"Å
RequestInfoProto.
	journalId (2.hadoop.hdfs.JournalIdProto
epoch (
ipcSerialNumber (
committedTxId ("M
SegmentStateProto
	startTxId (
endTxId (
isInProgress ("k
PersistedRecoveryPaxosData4
segmentState (2.hadoop.hdfs.SegmentStateProto
acceptedInEpoch ("ë
JournalRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto

firstTxnId (
numTxns (
records (
segmentTxnId ("
JournalResponseProto"G
HeartbeatRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto"
HeartbeatResponseProto"[
StartLogSegmentRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto
txid ("
StartLogSegmentResponseProto"t
FinalizeLogSegmentRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto
	startTxId (
endTxId ("!
FinalizeLogSegmentResponseProto"^
PurgeLogsRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto
minTxIdToKeep ("
PurgeLogsResponseProto"C
IsFormattedRequestProto(
jid (2.hadoop.hdfs.JournalIdProto"/
IsFormattedResponseProto
isFormatted ("G
GetJournalStateRequestProto(
jid (2.hadoop.hdfs.JournalIdProto"K
GetJournalStateResponseProto
lastPromisedEpoch (
httpPort ("o
FormatRequestProto(
jid (2.hadoop.hdfs.JournalIdProto/
nsInfo (2.hadoop.hdfs.NamespaceInfoProto"
FormatResponseProto"Ä
NewEpochRequestProto(
jid (2.hadoop.hdfs.JournalIdProto/
nsInfo (2.hadoop.hdfs.NamespaceInfoProto
epoch ("0
NewEpochResponseProto
lastSegmentTxId ("]
GetEditLogManifestRequestProto(
jid (2.hadoop.hdfs.JournalIdProto
	sinceTxId ("n
GetEditLogManifestResponseProto9
manifest (2'.hadoop.hdfs.RemoteEditLogManifestProto
httpPort ("b
PrepareRecoveryRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto
segmentTxId ("°
PrepareRecoveryResponseProto4
segmentState (2.hadoop.hdfs.SegmentStateProto
acceptedInEpoch (
lastWriterEpoch (
lastCommittedTxId ("î
AcceptRecoveryRequestProto.
reqInfo (2.hadoop.hdfs.RequestInfoProto5
stateToAccept (2.hadoop.hdfs.SegmentStateProto
fromURL (	"
AcceptRecoveryResponseProto2ê	
QJournalProtocolServiceZ
isFormatted$.hadoop.hdfs.IsFormattedRequestProto%.hadoop.hdfs.IsFormattedResponseProtof
getJournalState(.hadoop.hdfs.GetJournalStateRequestProto).hadoop.hdfs.GetJournalStateResponseProtoQ
newEpoch!.hadoop.hdfs.NewEpochRequestProto".hadoop.hdfs.NewEpochResponseProtoK
format.hadoop.hdfs.FormatRequestProto .hadoop.hdfs.FormatResponseProtoN
journal .hadoop.hdfs.JournalRequestProto!.hadoop.hdfs.JournalResponseProtoT
	heartbeat".hadoop.hdfs.HeartbeatRequestProto#.hadoop.hdfs.HeartbeatResponseProtof
startLogSegment(.hadoop.hdfs.StartLogSegmentRequestProto).hadoop.hdfs.StartLogSegmentResponseProtoo
finalizeLogSegment+.hadoop.hdfs.FinalizeLogSegmentRequestProto,.hadoop.hdfs.FinalizeLogSegmentResponseProtoT
	purgeLogs".hadoop.hdfs.PurgeLogsRequestProto#.hadoop.hdfs.PurgeLogsResponseProtoo
getEditLogManifest+.hadoop.hdfs.GetEditLogManifestRequestProto,.hadoop.hdfs.GetEditLogManifestResponseProtof
prepareRecovery(.hadoop.hdfs.PrepareRecoveryRequestProto).hadoop.hdfs.PrepareRecoveryResponseProtoc
acceptRecovery'.hadoop.hdfs.AcceptRecoveryRequestProto(.hadoop.hdfs.AcceptRecoveryResponseProtoBH
(org.apache.hadoop.hdfs.qjournal.protocolBQJournalProtocolProtosà†