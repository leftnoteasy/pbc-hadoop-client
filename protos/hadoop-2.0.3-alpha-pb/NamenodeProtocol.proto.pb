
Ñ
NamenodeProtocol.protohadoop.hdfs
hdfs.proto"U
GetBlocksRequestProto.
datanode (2.hadoop.hdfs.DatanodeIDProto
size ("O
GetBlocksResponseProto5
blocks (2%.hadoop.hdfs.BlocksWithLocationsProto"
GetBlockKeysRequestProto"N
GetBlockKeysResponseProto1
keys (2#.hadoop.hdfs.ExportedBlockKeysProto"
GetTransactionIdRequestProto"-
GetTransactionIdResponseProto
txId ("
RollEditLogRequestProto"T
RollEditLogResponseProto8
	signature (2%.hadoop.hdfs.CheckpointSignatureProto")
'GetMostRecentCheckpointTxIdRequestProto"8
(GetMostRecentCheckpointTxIdResponseProto
txId ("w
ErrorReportRequestProto<
registration (2&.hadoop.hdfs.NamenodeRegistrationProto
	errorCode (
msg (	"
ErrorReportResponseProto"T
RegisterRequestProto<
registration (2&.hadoop.hdfs.NamenodeRegistrationProto"U
RegisterResponseProto<
registration (2&.hadoop.hdfs.NamenodeRegistrationProto"[
StartCheckpointRequestProto<
registration (2&.hadoop.hdfs.NamenodeRegistrationProto"R
StartCheckpointResponseProto2
command (2!.hadoop.hdfs.NamenodeCommandProto"“
EndCheckpointRequestProto<
registration (2&.hadoop.hdfs.NamenodeRegistrationProto8
	signature (2%.hadoop.hdfs.CheckpointSignatureProto"
EndCheckpointResponseProto"3
GetEditLogManifestRequestProto
	sinceTxId ("\
GetEditLogManifestResponseProto9
manifest (2'.hadoop.hdfs.RemoteEditLogManifestProto2ã
NamenodeProtocolServiceT
	getBlocks".hadoop.hdfs.GetBlocksRequestProto#.hadoop.hdfs.GetBlocksResponseProto]
getBlockKeys%.hadoop.hdfs.GetBlockKeysRequestProto&.hadoop.hdfs.GetBlockKeysResponseProtoi
getTransactionId).hadoop.hdfs.GetTransactionIdRequestProto*.hadoop.hdfs.GetTransactionIdResponseProtoŠ
getMostRecentCheckpointTxId4.hadoop.hdfs.GetMostRecentCheckpointTxIdRequestProto5.hadoop.hdfs.GetMostRecentCheckpointTxIdResponseProtoZ
rollEditLog$.hadoop.hdfs.RollEditLogRequestProto%.hadoop.hdfs.RollEditLogResponseProtoU
versionRequest .hadoop.hdfs.VersionRequestProto!.hadoop.hdfs.VersionResponseProtoZ
errorReport$.hadoop.hdfs.ErrorReportRequestProto%.hadoop.hdfs.ErrorReportResponseProtoQ
register!.hadoop.hdfs.RegisterRequestProto".hadoop.hdfs.RegisterResponseProtof
startCheckpoint(.hadoop.hdfs.StartCheckpointRequestProto).hadoop.hdfs.StartCheckpointResponseProto`
endCheckpoint&.hadoop.hdfs.EndCheckpointRequestProto'.hadoop.hdfs.EndCheckpointResponseProtoo
getEditLogManifest+.hadoop.hdfs.GetEditLogManifestRequestProto,.hadoop.hdfs.GetEditLogManifestResponseProtoBE
%org.apache.hadoop.hdfs.protocol.protoBNamenodeProtocolProtosˆ 