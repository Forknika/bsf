#pragma once

#include "CmPrerequisites.h"
#include "CmIndexBuffer.h"

namespace CamelotEngine 
{
	/** Summary class collecting together index data source information. */
	class CM_EXPORT IndexData
	{
    public:
        IndexData();
        ~IndexData();
		/// pointer to the HardwareIndexBuffer to use, must be specified if useIndexes = true
		IndexBufferPtr indexBuffer;

		/// index in the buffer to start from for this operation
		UINT32 indexStart;

		/// The number of indexes to use from the buffer
		UINT32 indexCount;

		/** Clones this index data, potentially including replicating the index buffer.
		@param copyData Whether to create new buffers too or just reference the existing ones
		@param mgr If supplied, the buffer manager through which copies should be made
		@remarks The caller is expected to delete the returned pointer when finished
		*/
		IndexData* clone(bool copyData = true, HardwareBufferManager* mgr = 0) const;

		/** Re-order the indexes in this index data structure to be more
			vertex cache friendly; that is to re-use the same vertices as close
			together as possible. 
		@remarks
			Can only be used for index data which consists of triangle lists.
			It would in fact be pointless to use it on triangle strips or fans
			in any case.
		*/
		void optimiseVertexCacheTriList(void);

	protected:
		/// Protected copy constructor, to prevent misuse
		IndexData(const IndexData& rhs); /* do nothing, should not use */
		/// Protected operator=, to prevent misuse
		IndexData& operator=(const IndexData& rhs); /* do not use */
	};
}