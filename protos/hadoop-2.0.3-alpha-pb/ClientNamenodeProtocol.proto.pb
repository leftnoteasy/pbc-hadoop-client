
ÿP
ClientNamenodeProtocol.protohadoop.hdfsSecurity.proto
hdfs.proto"L
GetBlockLocationsRequestProto
src (	
offset (
length ("T
GetBlockLocationsResponseProto2
	locations (2.hadoop.hdfs.LocatedBlocksProto"
GetServerDefaultsRequestProto"\
GetServerDefaultsResponseProto:
serverDefaults (2".hadoop.hdfs.FsServerDefaultsProto"·
CreateRequestProto
src (	.
masked (2.hadoop.hdfs.FsPermissionProto

clientName (	

createFlag (
createParent (
replication (
	blockSize ("
CreateResponseProto"5
AppendRequestProto
src (	

clientName (	"D
AppendResponseProto-
block (2.hadoop.hdfs.LocatedBlockProto">
SetReplicationRequestProto
src (	
replication ("-
SetReplicationResponseProto
result ("\
SetPermissionRequestProto
src (	2

permission (2.hadoop.hdfs.FsPermissionProto"
SetPermissionResponseProto"H
SetOwnerRequestProto
src (	
username (	
	groupname (	"
SetOwnerResponseProto"c
AbandonBlockRequestProto*
b (2.hadoop.hdfs.ExtendedBlockProto
src (	
holder (	"
AbandonBlockResponseProto" 
AddBlockRequestProto
src (	

clientName (	1
previous (2.hadoop.hdfs.ExtendedBlockProto4
excludeNodes (2.hadoop.hdfs.DatanodeInfoProto"F
AddBlockResponseProto-
block (2.hadoop.hdfs.LocatedBlockProto"ó
!GetAdditionalDatanodeRequestProto
src (	,
blk (2.hadoop.hdfs.ExtendedBlockProto1
	existings (2.hadoop.hdfs.DatanodeInfoProto0
excludes (2.hadoop.hdfs.DatanodeInfoProto
numAdditionalNodes (

clientName (	"S
"GetAdditionalDatanodeResponseProto-
block (2.hadoop.hdfs.LocatedBlockProto"f
CompleteRequestProto
src (	

clientName (	-
last (2.hadoop.hdfs.ExtendedBlockProto"'
CompleteResponseProto
result ("M
ReportBadBlocksRequestProto.
blocks (2.hadoop.hdfs.LocatedBlockProto"
ReportBadBlocksResponseProto"/
ConcatRequestProto
trg (	
srcs (	"
ConcatResponseProto".
RenameRequestProto
src (	
dst (	"%
RenameResponseProto
result ("F
Rename2RequestProto
src (	
dst (	
overwriteDest ("
Rename2ResponseProto"4
DeleteRequestProto
src (	
	recursive ("%
DeleteResponseProto
result ("g
MkdirsRequestProto
src (	.
masked (2.hadoop.hdfs.FsPermissionProto
createParent ("%
MkdirsResponseProto
result ("O
GetListingRequestProto
src (	

startAfter (
needLocation ("N
GetListingResponseProto3
dirList (2".hadoop.hdfs.DirectoryListingProto",
RenewLeaseRequestProto

clientName (	"
RenewLeaseResponseProto";
RecoverLeaseRequestProto
src (	

clientName (	"+
RecoverLeaseResponseProto
result ("
GetFsStatusRequestProto"–
GetFsStatsResponseProto
capacity (
used (
	remaining (
under_replicated (
corrupt_blocks (
missing_blocks ("S
GetDatanodeReportRequestProto2
type (2$.hadoop.hdfs.DatanodeReportTypeProto"L
GetDatanodeReportResponseProto*
di (2.hadoop.hdfs.DatanodeInfoProto"5
!GetPreferredBlockSizeRequestProto
filename (	"3
"GetPreferredBlockSizeResponseProto
bsize ("c
SetSafeModeRequestProto0
action (2 .hadoop.hdfs.SafeModeActionProto
checked (:false"*
SetSafeModeResponseProto
result ("
SaveNamespaceRequestProto"
SaveNamespaceResponseProto"
RollEditsRequestProto"0
RollEditsResponseProto
newSegmentTxId ("/
 RestoreFailedStorageRequestProto
arg (	"3
!RestoreFailedStorageResponseProto
result ("
RefreshNodesRequestProto"
RefreshNodesResponseProto"
FinalizeUpgradeRequestProto"
FinalizeUpgradeResponseProto"A
!ListCorruptFileBlocksRequestProto
path (	
cookie (	"Z
"ListCorruptFileBlocksResponseProto4
corrupt (2#.hadoop.hdfs.CorruptFileBlocksProto"(
MetaSaveRequestProto
filename (	"
MetaSaveResponseProto"&
GetFileInfoRequestProto
src (	"H
GetFileInfoResponseProto,
fs (2 .hadoop.hdfs.HdfsFileStatusProto"*
GetFileLinkInfoRequestProto
src (	"L
GetFileLinkInfoResponseProto,
fs (2 .hadoop.hdfs.HdfsFileStatusProto"-
GetContentSummaryRequestProto
path (	"S
GetContentSummaryResponseProto1
summary (2 .hadoop.hdfs.ContentSummaryProto"T
SetQuotaRequestProto
path (	
namespaceQuota (
diskspaceQuota ("
SetQuotaResponseProto"M
FsyncRequestProto
src (	
client (	
lastBlockLength (:-1"
FsyncResponseProto"A
SetTimesRequestProto
src (	
mtime (
atime ("
SetTimesResponseProto"€
CreateSymlinkRequestProto
target (	
link (	/
dirPerm (2.hadoop.hdfs.FsPermissionProto
createParent ("
CreateSymlinkResponseProto")
GetLinkTargetRequestProto
path (	"0
GetLinkTargetResponseProto

targetPath (	"h
"UpdateBlockForPipelineRequestProto.
block (2.hadoop.hdfs.ExtendedBlockProto

clientName (	"T
#UpdateBlockForPipelineResponseProto-
block (2.hadoop.hdfs.LocatedBlockProto"Æ
UpdatePipelineRequestProto

clientName (	1
oldBlock (2.hadoop.hdfs.ExtendedBlockProto1
newBlock (2.hadoop.hdfs.ExtendedBlockProto.
newNodes (2.hadoop.hdfs.DatanodeIDProto"
UpdatePipelineResponseProto"5
 SetBalancerBandwidthRequestProto
	bandwidth ("#
!SetBalancerBandwidthResponseProto""
 GetDataEncryptionKeyRequestProto"c
!GetDataEncryptionKeyResponseProto>
dataEncryptionKey (2#.hadoop.hdfs.DataEncryptionKeyProto*8
CreateFlagProto

CREATE
	OVERWRITE

APPEND*6
DatanodeReportTypeProto
ALL
LIVE
DEAD*O
SafeModeActionProto
SAFEMODE_LEAVE
SAFEMODE_ENTER
SAFEMODE_GET2©#
ClientNamenodeProtocoll
getBlockLocations*.hadoop.hdfs.GetBlockLocationsRequestProto+.hadoop.hdfs.GetBlockLocationsResponseProtol
getServerDefaults*.hadoop.hdfs.GetServerDefaultsRequestProto+.hadoop.hdfs.GetServerDefaultsResponseProtoK
create.hadoop.hdfs.CreateRequestProto .hadoop.hdfs.CreateResponseProtoK
append.hadoop.hdfs.AppendRequestProto .hadoop.hdfs.AppendResponseProtoc
setReplication'.hadoop.hdfs.SetReplicationRequestProto(.hadoop.hdfs.SetReplicationResponseProto`
setPermission&.hadoop.hdfs.SetPermissionRequestProto'.hadoop.hdfs.SetPermissionResponseProtoQ
setOwner!.hadoop.hdfs.SetOwnerRequestProto".hadoop.hdfs.SetOwnerResponseProto]
abandonBlock%.hadoop.hdfs.AbandonBlockRequestProto&.hadoop.hdfs.AbandonBlockResponseProtoQ
addBlock!.hadoop.hdfs.AddBlockRequestProto".hadoop.hdfs.AddBlockResponseProtox
getAdditionalDatanode..hadoop.hdfs.GetAdditionalDatanodeRequestProto/.hadoop.hdfs.GetAdditionalDatanodeResponseProtoQ
complete!.hadoop.hdfs.CompleteRequestProto".hadoop.hdfs.CompleteResponseProtof
reportBadBlocks(.hadoop.hdfs.ReportBadBlocksRequestProto).hadoop.hdfs.ReportBadBlocksResponseProtoK
concat.hadoop.hdfs.ConcatRequestProto .hadoop.hdfs.ConcatResponseProtoK
rename.hadoop.hdfs.RenameRequestProto .hadoop.hdfs.RenameResponseProtoN
rename2 .hadoop.hdfs.Rename2RequestProto!.hadoop.hdfs.Rename2ResponseProtoK
delete.hadoop.hdfs.DeleteRequestProto .hadoop.hdfs.DeleteResponseProtoK
mkdirs.hadoop.hdfs.MkdirsRequestProto .hadoop.hdfs.MkdirsResponseProtoW

getListing#.hadoop.hdfs.GetListingRequestProto$.hadoop.hdfs.GetListingResponseProtoW

renewLease#.hadoop.hdfs.RenewLeaseRequestProto$.hadoop.hdfs.RenewLeaseResponseProto]
recoverLease%.hadoop.hdfs.RecoverLeaseRequestProto&.hadoop.hdfs.RecoverLeaseResponseProtoX

getFsStats$.hadoop.hdfs.GetFsStatusRequestProto$.hadoop.hdfs.GetFsStatsResponseProtol
getDatanodeReport*.hadoop.hdfs.GetDatanodeReportRequestProto+.hadoop.hdfs.GetDatanodeReportResponseProtox
getPreferredBlockSize..hadoop.hdfs.GetPreferredBlockSizeRequestProto/.hadoop.hdfs.GetPreferredBlockSizeResponseProtoZ
setSafeMode$.hadoop.hdfs.SetSafeModeRequestProto%.hadoop.hdfs.SetSafeModeResponseProto`
saveNamespace&.hadoop.hdfs.SaveNamespaceRequestProto'.hadoop.hdfs.SaveNamespaceResponseProtoT
	rollEdits".hadoop.hdfs.RollEditsRequestProto#.hadoop.hdfs.RollEditsResponseProtou
restoreFailedStorage-.hadoop.hdfs.RestoreFailedStorageRequestProto..hadoop.hdfs.RestoreFailedStorageResponseProto]
refreshNodes%.hadoop.hdfs.RefreshNodesRequestProto&.hadoop.hdfs.RefreshNodesResponseProtof
finalizeUpgrade(.hadoop.hdfs.FinalizeUpgradeRequestProto).hadoop.hdfs.FinalizeUpgradeResponseProtox
listCorruptFileBlocks..hadoop.hdfs.ListCorruptFileBlocksRequestProto/.hadoop.hdfs.ListCorruptFileBlocksResponseProtoQ
metaSave!.hadoop.hdfs.MetaSaveRequestProto".hadoop.hdfs.MetaSaveResponseProtoZ
getFileInfo$.hadoop.hdfs.GetFileInfoRequestProto%.hadoop.hdfs.GetFileInfoResponseProtof
getFileLinkInfo(.hadoop.hdfs.GetFileLinkInfoRequestProto).hadoop.hdfs.GetFileLinkInfoResponseProtol
getContentSummary*.hadoop.hdfs.GetContentSummaryRequestProto+.hadoop.hdfs.GetContentSummaryResponseProtoQ
setQuota!.hadoop.hdfs.SetQuotaRequestProto".hadoop.hdfs.SetQuotaResponseProtoH
fsync.hadoop.hdfs.FsyncRequestProto.hadoop.hdfs.FsyncResponseProtoQ
setTimes!.hadoop.hdfs.SetTimesRequestProto".hadoop.hdfs.SetTimesResponseProto`
createSymlink&.hadoop.hdfs.CreateSymlinkRequestProto'.hadoop.hdfs.CreateSymlinkResponseProto`
getLinkTarget&.hadoop.hdfs.GetLinkTargetRequestProto'.hadoop.hdfs.GetLinkTargetResponseProto{
updateBlockForPipeline/.hadoop.hdfs.UpdateBlockForPipelineRequestProto0.hadoop.hdfs.UpdateBlockForPipelineResponseProtoc
updatePipeline'.hadoop.hdfs.UpdatePipelineRequestProto(.hadoop.hdfs.UpdatePipelineResponseProtos
getDelegationToken-.hadoop.common.GetDelegationTokenRequestProto..hadoop.common.GetDelegationTokenResponseProtoy
renewDelegationToken/.hadoop.common.RenewDelegationTokenRequestProto0.hadoop.common.RenewDelegationTokenResponseProto|
cancelDelegationToken0.hadoop.common.CancelDelegationTokenRequestProto1.hadoop.common.CancelDelegationTokenResponseProtou
setBalancerBandwidth-.hadoop.hdfs.SetBalancerBandwidthRequestProto..hadoop.hdfs.SetBalancerBandwidthResponseProtou
getDataEncryptionKey-.hadoop.hdfs.GetDataEncryptionKeyRequestProto..hadoop.hdfs.GetDataEncryptionKeyResponseProtoBK
%org.apache.hadoop.hdfs.protocol.protoBClientNamenodeProtocolProtosˆ 