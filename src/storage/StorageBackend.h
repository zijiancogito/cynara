/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/**
 * @file        src/storage/StorageBackend.h
 * @author      Aleksander Zdyb <a.zdyb@samsung.com>
 * @version     1.0
 * @brief       Headers for StorageBackend base class
 */

#ifndef SRC_STORAGE_STORAGEBACKEND_H_
#define SRC_STORAGE_STORAGEBACKEND_H_

#include <string>

#include <types/pointers.h>
#include <types/PolicyBucket.h>
#include <types/PolicyKey.h>
#include <types/PolicyBucketId.h>
#include <types/PolicyResult.h>

namespace Cynara {

class StorageBackend {
public:
    virtual ~StorageBackend() {}

    // TODO: Remove searchDefaultBucket()
    virtual PolicyBucket searchDefaultBucket(const PolicyKey &key) = 0;
    virtual PolicyBucket searchBucket(const PolicyBucketId &bucket, const PolicyKey &key) = 0;

    virtual void insertPolicy(const PolicyBucketId &bucket, PolicyPtr policy) = 0;

    virtual void createBucket(const PolicyBucketId &bucketId,
                              const PolicyResult &defaultPolicy) = 0;
    virtual void updateBucket(const PolicyBucketId &bucketId,
                              const PolicyResult &defaultPolicy) = 0;
    virtual void deleteBucket(const PolicyBucketId &bucketId) = 0;
    virtual bool hasBucket(const PolicyBucketId &bucketId) = 0;

    virtual void deletePolicy(const PolicyBucketId &bucketId, const PolicyKey &key) = 0;
    virtual void deleteLinking(const PolicyBucketId &bucket) = 0;
    virtual PolicyBucket::Policies listPolicies(const PolicyBucketId &bucketId,
                                                const PolicyKey &filter) const = 0;
    virtual void erasePolicies(const PolicyBucketId &bucketId, bool recursive,
                               const PolicyKey &filter) = 0;
    virtual void load(void) = 0;
    virtual void save(void) = 0;
};

} /* namespace Cynara */

#endif /* SRC_STORAGE_STORAGEBACKEND_H_ */
