
ã
JournalProtocol.protohadoop.hdfs
hdfs.proto"Q
JournalInfoProto
	clusterID (	
layoutVersion (
namespaceID ("Ž
JournalRequestProto2
journalInfo (2.hadoop.hdfs.JournalInfoProto

firstTxnId (
numTxns (
records (
epoch ("
JournalResponseProto"n
StartLogSegmentRequestProto2
journalInfo (2.hadoop.hdfs.JournalInfoProto
txid (
epoch ("
StartLogSegmentResponseProto"j
FenceRequestProto2
journalInfo (2.hadoop.hdfs.JournalInfoProto
epoch (

fencerInfo (	"V
FenceResponseProto
previousEpoch (
lastTransactionId (
inSync (2š
JournalProtocolServiceN
journal .hadoop.hdfs.JournalRequestProto!.hadoop.hdfs.JournalResponseProtof
startLogSegment(.hadoop.hdfs.StartLogSegmentRequestProto).hadoop.hdfs.StartLogSegmentResponseProtoH
fence.hadoop.hdfs.FenceRequestProto.hadoop.hdfs.FenceResponseProtoBD
%org.apache.hadoop.hdfs.protocol.protoBJournalProtocolProtosˆ 